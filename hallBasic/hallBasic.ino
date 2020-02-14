// NOTE: if you want to use more pins the 2 (2&3) - see hallMulti folder

const byte ledPin = 13;
const byte interruptPin = 0; // !!! Actually, It's pin 2, attachInterrupt only works with pins 2 & 3 (0,1)
volatile byte state = LOW;
volatile byte oldState = LOW;

void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(interruptPin, INPUT_PULLUP);
 attachInterrupt(interruptPin, changeState, CHANGE);
 Serial.begin(9600);
}

void loop() {
 digitalWrite(ledPin, state);
 if (oldState != state) {
    Serial.println(state);
    oldState = state;
 }  
}

void changeState() {
 state = !state;
}
