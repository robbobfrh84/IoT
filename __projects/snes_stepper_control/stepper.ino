int stepperDir = LOW; // Counter Clockwise, HIGH = Clockwise

void setupStepper() {
  pinMode(stepperPinsX[0], OUTPUT);
  pinMode(stepperPinsX[1], OUTPUT);
  pinMode(stepperPinsY[0], OUTPUT);
  pinMode(stepperPinsY[1], OUTPUT); 
  pinMode(stepperPinsZ[0], OUTPUT);
  pinMode(stepperPinsZ[1], OUTPUT);
  digitalWrite(stepperPinsX[0], stepperDir);
  digitalWrite(stepperPinsX[1], stepperDir);
  
  digitalWrite(stepperPinsY[0], stepperDir);
  digitalWrite(stepperPinsY[1], stepperDir);
  digitalWrite(stepperPinsZ[0], stepperDir);
  digitalWrite(stepperPinsZ[1], stepperDir);
}

void stepper(long int steps, int dir, long int delaySteps, int pin[2]) {  
  if (stepperDir != dir) {
    digitalWrite(pin[0], dir);
    stepperDir = dir;
  }
  long int adjustSpeed = delaySteps;
  if (steps > 8) {
    delaySteps += 20;
  }
  for (long int i =  0; i < steps; i++) {
    digitalWrite(pin[1], HIGH);
    delayMicroseconds(delaySteps);         
    digitalWrite(pin[1], LOW);
    delayMicroseconds(delaySteps);  
  }
}
