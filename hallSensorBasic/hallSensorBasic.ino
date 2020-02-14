const byte ledPin = 7;
const byte interruptPin = 8;
volatile byte state = LOW;
int val=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), test, CHANGE);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ledPin, state);
  Serial.println(val/2);
}

void test() {
  state = !state;
  val++;
}
