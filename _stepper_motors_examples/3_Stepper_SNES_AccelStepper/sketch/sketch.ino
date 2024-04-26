#include <AccelStepper.h> // * DOCS: https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html

/* 📍 Pins 📌 */
const int snesPins[3] = {8,9,10}; // * Latch,Clock,Data (yellow,blue,red) | 5v (white wire), Ground = (brown/black wire)

AccelStepper stepperX(1, 2, 3); int ENA_X=4; // * define Enable Pin
AccelStepper stepperY(1, 5, 6); int ENA_Y=7; 
AccelStepper stepperZ(1, A0, A1); int ENA_Z=A2; 

/* 🪜 Control / Settings Vars 🎛️ */ 
const bool limitSteps = false; // * If true, held buttons will stop to following 👇 XYZ limits. If false, holding snes direction buttons down will run forever.
const int Xsteps = 6000; // * 800 / 4 * 30 = 6000 -> (steps per rotation) / (cm traveled per rotation) * (cm) 
const int Ysteps = 6000; // * 800 / 4 * 30 = 6000 -> (steps per rotation) / (cm traveled per rotation) * (cm) 
const int Zsteps = 1600; // * 800 / 4 * 8 = 1600 -> (steps per rotation) / (cm traveled per rotation) * (cm) 

const int revSteps = 200; // * Steps per revolution. Changing microstep rate done on motor driver. 
const int microSteps = 4; // * Micro Steps per single Step. Set on Motor Driver. 
const int longChunkDelay = 500; // * In millis. How long to wait between small short steps, single/full step, etc...
const int shortChunkDelay = 100; // * In millis. How long to wait between larger steps, 1/4 rotate, full rotate etc...
const int acceleration = 3200.0; // * 3600.0 MAX - It just behaves better at this round number than other number, idk. other number have weird delays that are much longer below this and even obove. some kind of rounding issues I'm guessing. 
const int maxSpeed = 1600.0; // * 1600 MAX - Looks to be max speed while reading SNES very void loop
const float speeds[5] = { 0.025, 0.1, 0.33, 0.66, 1 }; // maxSpeed fractions.
const long holdForSpeedChange = 1000;  // * How long we break for while holding 'Y' the speed change button.

/* 😇 Global Vars 😇 */
static bool snes[13] = {}; // * SNES Buttons Indexes as { anyPressed, B, Y, Se, St, U, D, L, R, A, X, Lt, Rt }
int speedIndex = sizeof(speeds) / sizeof(speeds[0]) - 1;
int currentSpeed = speeds[speedIndex] * maxSpeed; 
unsigned long lastSpeedChangeMillis = 0;  // * the last time the speed change was made (see holdForSpeedChange)
bool xGo = false; bool yGo = false; bool zGo = false; // * Controller Axis motor state.
bool xStopped = true; bool yStopped = true; bool zStopped = true; // * Lets SNES controller know when motors have stopped. 


void setup() {  
  Serial.begin(115200);
  setupSnes();

  stepperX.setEnablePin();
  stepperX.setMaxSpeed(currentSpeed);
  stepperX.setAcceleration(acceleration);

  stepperY.setEnablePin();
  stepperY.setMaxSpeed(currentSpeed);
  stepperY.setAcceleration(acceleration);

  stepperZ.setEnablePin();
  stepperZ.setMaxSpeed(currentSpeed);
  stepperZ.setAcceleration(acceleration);

  stepperX.runToNewPosition(0);
  stepperY.runToNewPosition(0);
  stepperY.runToNewPosition(0);
}

void loop() { mainLoop(); }