String snes;
const int snesPins[3] = {2,3,4}; // Latch,Clock,Data (yellow,blue,red) *5v=white,Ground=brown/black
const int stepperPinsX[2] = {7,8}; // Direction, Step
const int stepperPinsY[2] = {9,10}; // Direction, Step
const int stepperPinsZ[2] = {11,12}; // Direction, Step

const int stepsInRotation = 1600;
long int stepTracker = 0;
long int fullSteps = 1;
int speedSet = 3;
const int totalspeeds = 7;
const int speeds[totalspeeds] = {3200,1600,800,400,200,100,50}; // Slowest -> Fastest

void setup() {
  Serial.begin(115200);
  setupSnes();
  setupStepper();
} 

void loop(){
  snes = getSnesButton();
  if (snes != "") {
    for (int i = 0; i < snes.length(); i++) {
      handleButtonsPressed(String(snes[i]));
    }
  } else {
    fullSteps = 1;
  }
}

void handleButtonsPressed(String btn) {
  if (btn == "L") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, LOW, speeds[speedSet], stepperPinsX);
    stepTracker -= 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "R") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, HIGH, speeds[speedSet], stepperPinsX);
    stepTracker += 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "D") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, LOW, speeds[speedSet], stepperPinsY);
    stepTracker -= 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "U") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, HIGH, speeds[speedSet], stepperPinsY);
    stepTracker += 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "T") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, LOW, speeds[speedSet], stepperPinsZ);
    stepTracker -= 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "P") {
    const int moveSteps = 8*fullSteps;
    stepper(moveSteps, HIGH, speeds[speedSet], stepperPinsZ);
    stepTracker += 8*fullSteps;
    fullSteps = 1;
  } else if (btn == "B") {
    speedSet++;
    if (speedSet >= totalspeeds) {
      speedSet = totalspeeds - 1;
    }
    Serial.println("Speed: "+String(speeds[speedSet]));
    delay(200);
  } else if (btn == "A") {
    speedSet--;
    if (speedSet <= 0) {
      speedSet = 0;
    }
    Serial.println("Speed: "+String(speeds[speedSet]));
    delay(200);
  } else if (btn == "E") {
    Serial.println(" ----- ");
    Serial.print("Steps Clockwise (full,micro): "+String(stepTracker)+",");
    Serial.println(String(stepTracker*8));
    Serial.println("Rotations: "+String(float(stepTracker)/200));
    Serial.println("Speed: "+String(speedSet)+" - "+String(speeds[speedSet])+" delay");
    delay(200);
  } else if (btn == "S") {
    delay(200);
  } else if (btn == "Y") {
    fullSteps = 200; // 1 full rotation
  } else if (btn == "X") {
    fullSteps = 800; // 4 full rotation
  } 
}
