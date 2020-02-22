int hallPin = 2;
int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(hallPin,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  int hallPinState = digitalRead(hallPin);
  Serial.println("hallPinState: "+String(hallPinState));
  digitalWrite(ledPin, !hallPinState);
  delay(1);
}
