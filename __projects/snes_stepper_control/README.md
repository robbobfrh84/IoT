
# Snes controller stepper motor controller 

NOTE: this sketch combines two basic example sketches in this repo.
 
- _stepper_motors/easyDriver_nema17_ard
- snes_controller_ard

# Buttons

##### X-Axis Move (Pins 7=dir,8=step)
- Left D-pad(L): rotates X-axis stepper counter-clockwise
- Right D-pad(R): rotates X-axis stepper clockwise

##### Y-Axis Move (Pins 9=dir,10=step)
- Up D-pad(U): rotates X-axis stepper counter-clockwise
- Down D-pad(R): rotates X-axis stepper clockwise

##### Y-Axis Move (Pins 11=dir,12=step)
- Left D-pad(L): rotates X-axis stepper counter-clockwise
- Right D-pad(R): rotates X-axis stepper clockwise

##### Change Speed (3200,1600,800,400,200,100,50) <-slower, faster->
- A: 1 Speed down. Minimum out at 3200 microsecond delay. 
- B: 1 Speed up. Maxes out at 50 microsecond delay.

##### Set Lengths
- Y + Axis Move: 1 full rotation at set speed.
- X + Axis Move: 4 full rotation at set speed.
- Start(S) + Axis move(L,R): Single Full Step(8 micro) + 200ms delay

##### Options & info
- Select(E): Serial.prints step log & Current speed.




