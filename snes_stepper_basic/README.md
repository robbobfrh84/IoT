
# Snes controller stepper motor controller 

NOTE: this sketch combines two basic example sketches in this repo.
 
- _stepper_motors/easyDriver_nema17_ard
- snes_controller_ard

# Buttons
- Left D-pad(L): rotates X-axis stepper counter-clockwise
- Right D-pad(R): rotates X-axis stepper clockwise

- Select(E): Serial.prints step log & Current speed.
- Start(S) + Axis move(L,R): Single Full Step(8 micro) + 200ms delay

- A: 1 Speed down. Minimum out at 3200 microsecond delay. 
- B: 1 Speed up. Maxes out at 50 microsecond delay. 

- Y + Axis Move: 1 full rotation at set speed.
- X + Axis Move: 4 full rotation at set speed.

Speeds 

- {3200,1600,800,400,200,100,50}
