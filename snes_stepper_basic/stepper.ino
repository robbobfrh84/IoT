const int dirPin = stepperPins[0];
const int stepPin = stepperPins[1];
int stepperDir = LOW; // Counter Clockwise, HIGH = Clockwise

void setupStepper() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, stepperDir);
  digitalWrite(stepPin, stepperDir);
}

void stepper(long int steps, int dir, long int delaySteps) {  
  if (stepperDir != dir) {
    digitalWrite(dirPin, dir);
    stepperDir = dir;
  }
  long int adjustSpeed = delaySteps;
  if (steps > 8) {
    delaySteps += 20;
  }
  for (long int i =  0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delaySteps);         
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delaySteps);  
  }
}
