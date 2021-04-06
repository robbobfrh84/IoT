const int xDir = 8;
const int xPin = 9;
const int stepsInRotation = 1600;
const int long stepsInDirection = 3 * stepsInRotation;

int const delaySteps = 1; // faster the lower it is. 1000 = 1 second
int const microDelaySteps = 200; // 1000 = 1 delayStep. 1,000,000 = 1 second

int dir = LOW;
int count = 0;
int timer = millis();

void setup() {               
  Serial.begin(9600);
  pinMode(xDir, OUTPUT);
  pinMode(xPin, OUTPUT);
  digitalWrite(xDir, dir);
  digitalWrite(xPin, dir);
}

void loop() {
  count++;
  
  digitalWrite(xPin, HIGH);
  //delay(delaySteps);         
  delayMicroseconds(microDelaySteps);         

  digitalWrite(xPin, LOW);
  //delay(delaySteps);
  delayMicroseconds(microDelaySteps);         
  
  if (count == stepsInDirection) {
    count = 0;
    dir = dir == LOW ? HIGH : LOW;
    digitalWrite(xDir, dir);
    const int now = millis() - timer;
    Serial.println("delay: "+String(now));
    delay(1000);
    timer = millis();
  }
}
