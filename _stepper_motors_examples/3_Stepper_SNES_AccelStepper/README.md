# How it works
### **SNES Control**

**Control Buttons** (used with Motor Direction Buttons)

- Free Move: Hold **B** button down & select a direction(s) on D-pad or Top- Left/Right buttons.
  - This will move the motor(s) at the current speed rate
- Change Speed: Press **Y** button to cycle threw speeds 2.5%, 10%, 33%, 66%, and 100%
  - You can do this while running the motor in **Free Move (B)**.

- Move 1 Step: Hold **START** button & select a direction(s) on D-pad or top Left/Right buttons.
- Move 1-full Step: Hold **SELECT** button & select a direction(s) on D-pad or top Left/Right buttons.
- Move 1/4 Rotation: Hold **A** button down & select a direction(s) on D-pad or top Left/Right buttons.
- Move 1 full Rotation: Hold **X** button down & select a direction(s) on D-pad or top Left/Right buttons.

**Motor Directions Buttons** (A Control Button must be pressed to enable)

- D-Pad **Left / Right** controls **X-Axis.**
- D-Pad **Up / Down** controls **Y-Axis.**
- D-Pad **Top-Left / Top-Right** controls **Z-Axis.**

**Note:** These Classic SNES controllers can be a little faulty and sometime you need to release all buttons as it can get "stuck" in the button combo same action. But honestly it just works fine most of the time fine. 



### Components

- Arduino Uno
- Classic SNES controller (NOTE: common USB controllers found online won't work)
- 3x TB6600 Stepper Motor Drivers
- 3x 12v to 1.5amp Wall adapters *(could be different depending on motors)*
- 3x 12v 350amp Nema 17 Stepper Motors *(could be different depending on motors)*

### Wiring

- See code, pics and images for wiring

### NOTE: **This Sketch uses the "AccelStepper" Library**

- Link: https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#ae79c49ad69d5ccc9da0ee691fa4ca235
- However, there are some issues with this library that should be noted. **1 -** While changing directions works one way, the other way requires one step in the old (wrong) direction before stepped in the new reversed direction. I couldn't find anything about this issue and had to hack around the library by call the direction pin HIGH before reversing direction in the way that didn't work. **2 -** While the acceleration works great, it can't change speeds mid move. Meaning it must fully stop before changing the speed.

#  Resources

- Youtube: "Controlling 3 Stepper Motors with the AccelStepper Library for Arduino"

  - https://www.youtube.com/watch?v=QRCvC5xhJCw
  - Video includes a lot of code changes that show how to use moves of motors in different ways. 

- Used the wiring from this Guide: https://wiki.dfrobot.com/TB6600_Stepper_Motor_Driver_SKU__DRI0043

