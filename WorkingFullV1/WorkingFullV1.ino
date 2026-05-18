#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <SoftServo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IR_PIN        7
#define SPEAKER_PIN   8
#define SERVO_PIN     9
#define RELAY_PIN     6

SoftServo bombServo;

unsigned long button7 = 0xFF10EF;
unsigned long button8 = 0xFF38C7;
unsigned long button9 = 0xFF5AA5;

IRrecv irrecv(IR_PIN);
decode_results results;

unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 300;

bool countdownActive = false;
unsigned long startTime = 0;

// Capacitor delay (adjust to your actual explosion time)
const unsigned long CAP_DELAY_MS = 10000;   // 10 seconds
const unsigned long COUNTDOWN_DURATION_MS = CAP_DELAY_MS;

bool relayActivated = false;   // so we only turn it on once
bool boomTriggered = false;

unsigned long servoStart = 0;
bool servoMoving = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // *** FIX: For low‑level trigger, start with relay OFF = HIGH ***
  digitalWrite(RELAY_PIN, HIGH);   // HIGH = relay OFF (safe state)
  
  bombServo.attach(SERVO_PIN);
  bombServo.write(0);
  delay(300);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BombBot Ready");
  
  Serial.println("Ready - Press button 7");
  delay(1000);
}

void loop() {
  bombServo.tick();

  if (servoMoving && millis() - servoStart > 500) {
    bombServo.write(-10);
    servoMoving = false;
  }

  if (irrecv.decode(&results)) {
    if (millis() - lastPressTime > debounceDelay) {
      lastPressTime = millis();

      if (results.value == button7) {
        countdownActive = true;
        startTime = millis();
        relayActivated = false;
        boomTriggered = false;
        
        // *** FIX: Turn relay ON by setting LOW ***
        digitalWrite(RELAY_PIN, LOW);   // LOW = relay ON (for low‑level trigger)
        relayActivated = true;
        Serial.println("Relay ON - Capacitor charging (reverse polarity)");
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Countdown:");
        Serial.println("Countdown Started");
      }
      else if (results.value == button8 || results.value == button9) {
        Serial.println("Manual Servo Trigger");
        triggerServo();
      }
    }
    irrecv.resume();
  }

  if (countdownActive) {
    unsigned long elapsed = millis() - startTime;
    unsigned long remaining = (elapsed < COUNTDOWN_DURATION_MS) ? (COUNTDOWN_DURATION_MS - elapsed) : 0;

    lcd.setCursor(0, 1);
    lcd.print(remaining / 1000.0, 1);
    lcd.print("s   ");

    if (remaining == 0 && !boomTriggered) {
      boomTriggered = true;
      lcd.setCursor(0, 1);
      lcd.print("BOOM!       ");
      Serial.println("BOOM! Countdown finished");
      
      triggerServo();
      delay(100);
      bombServo.tick();
      boom();
      
      // Turn relay OFF after explosion (optional but safe)
      digitalWrite(RELAY_PIN, HIGH);   // HIGH = relay OFF
      Serial.println("Relay OFF");
      
      countdownActive = false;
    }
  }
}

void triggerServo() {
  Serial.println("Servo moving to 90°...");
  bombServo.write(140);
  servoStart = millis();
  servoMoving = true;
}

void boom() {
  // Your original boom sound function – unchanged
  for (int repeat = 0; repeat < 3; repeat++) {
    tone(SPEAKER_PIN, 2500);
    delay(30);
    bombServo.tick();
    noTone(SPEAKER_PIN);
    delay(10);
    bombServo.tick();
  }
  for (int i = 0; i < 200; i++) {
    tone(SPEAKER_PIN, random(40, 2000));
    delay(random(2, 8));
    bombServo.tick();
  }
  for (int f = 800; f > 30; f -= 3) {
    tone(SPEAKER_PIN, f);
    delay(6);
    bombServo.tick();
  }
  for (int i = 0; i < 50; i++) {
    tone(SPEAKER_PIN, random(30, 200));
    delay(random(5, 20));
    noTone(SPEAKER_PIN);
    delay(random(2, 10));
  }
  noTone(SPEAKER_PIN);
}