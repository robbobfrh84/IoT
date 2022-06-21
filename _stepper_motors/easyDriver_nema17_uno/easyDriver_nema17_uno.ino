const int xDir = 12;
const int xPin = 13;
const int stepsInRotation = 1600;
const int long stepsInDirection = 4 * stepsInRotation;

int const delaySteps = 1; // faster the lower it is. 1000 = 1 second
int const microDelaySteps = 400; // 1000 = 1 delayStep. 1,000,000 = 1 second

int dir = LOW;
int count = 0;
int timer = millis();
//bool onOff = HIGH;

void setup() {               
  Serial.begin(9600);
  pinMode(xDir, OUTPUT);
  pinMode(xPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(xDir, dir);
  digitalWrite(xPin, dir);
//  digitalWrite(LED_BUILTIN, onOff);
}

void loop() {
  count++;
  
  digitalWrite(xPin, HIGH);
  delayMicroseconds(microDelaySteps);         

  digitalWrite(xPin, LOW);
  delayMicroseconds(microDelaySteps);         
  
  if (count == stepsInDirection) {
    count = 0;
    dir = dir == LOW ? HIGH : LOW;
    digitalWrite(xDir, dir);
    const int now = millis() - timer;
    Serial.println("delay: "+String(now/4)+" ms per rotation");
//    onOff = !onOff;
//    digitalWrite(LED_BUILTIN, onOff);
    delay(1000);
    timer = millis();
  }
}
