# Varsity-Sackers
<img width="3668" height="4612" alt="IMG_9062" src="https://github.com/user-attachments/assets/1ff3a523-f0f1-4973-95b2-e3df48ed81eb" />

# **Konfetti Kaboom**
Konfetti Kaboom (otherwise known [by our german brotha from another mother] as Bombawagen) is a code/remote-controlled robot equipped with an over-engineered confetti cannon. Using just a single servo motor, we were able to convert rotational movement into linear motion with the pull of a pin to release our cannon. Using an Arduino Uno R3, we also rigged up a capacitor to produce a loud bang, like most confetti cannons do. The robot can be remote-controlled, but also features a built-in game mode. The game is similar to the well-known game of Russian roulette. It works by having several people gather in a circle and then start the robot. The robot autonomously turns in different directions and returns to the center each time. It then randomly picks a direction and drives that way for a few seconds. At that moment, the capacitor detonates and the confetti cannon is triggered.

# **Technical Description**
The drive motors are powered by the battery provided with the Elegoo V3 kit. In addition, there are several 9V batteries used to detonate the capacitor, and one 9V battery is used to power the servo that controls the confetti cannon. Two Arduino Uno R3 boards handle the system control. One Arduino is responsible for motor control, while the other controls the cannon, the detonation of the capacitor, and the LCD display. To allow the Arduino to execute commands, we used an IR receiver to send signals from the remote control to the Arduino Uno R3. At this hackathon, there was also a specific theme requiring you to choose a random item and build it into your project. Ours was an alarm clock from the 70s or 80s. From this alarm clock, we extracted the housing and the buzzer, which can play sounds. We glued the VFD from the alarm clock onto the back of the vehicle as decoration.

# **Prototype v1 Catapult Demo Video**
https://youtu.be/Vskx_DW9xjM

# **Demo Game**
https://youtu.be/gEPX9HXMvCo

# **Movement**
-The movement is already coded within the Arduino that was supplied with the Robot Kit
-For the confetti launcher we

# **Creators:**  Delong Liu, Ethan Bailey, Jack Reisdorph

