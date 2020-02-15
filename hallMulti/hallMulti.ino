const int ledPins[] = {9,10,11,12,13};
const int hallPins[] = {2,3,4,5,6}; 
const int totalHallPins = sizeof(hallPins)/sizeof(hallPins[0]);

void setup() {
  for (int i = 0; i < totalHallPins; i++) {
    pinMode(hallPins[i],INPUT);
    pinMode(ledPins[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < totalHallPins; i++) {
    const boolean state = digitalRead(hallPins[i]);
    digitalWrite(ledPins[i], !state);
  }
}

/*

OPTION 2: simplified without loops

int hallPin1 = 2;
int hallPin2 = 3;
int hallPin3 = 4;
int hallPin4 = 5;
int hallPin5 = 6;

int ledPin1 = 9;
int ledPin2 = 10;
int ledPin3 = 11;
int ledPin4 = 12;
int ledPin5 = 13;

void setup() {
  Serial.begin(9600);
  pinMode(hallPin1,INPUT);
  pinMode(hallPin2,INPUT);
  pinMode(hallPin3,INPUT);
  pinMode(hallPin4,INPUT);
  pinMode(hallPin5,INPUT);

  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
}

void loop() {
  int hallPinState1 = digitalRead(hallPin1);
  int hallPinState2 = digitalRead(hallPin2);
  int hallPinState3 = digitalRead(hallPin3);
  int hallPinState4 = digitalRead(hallPin4);
  int hallPinState5 = digitalRead(hallPin5);

  Serial.println("Pin states: "+String(hallPinState1)+String(hallPinState2)+String(hallPinState3)+String(hallPinState4)+String(hallPinState5));
  
  digitalWrite(ledPin1, !hallPinState1);
  digitalWrite(ledPin2, !hallPinState2);
  digitalWrite(ledPin3, !hallPinState3);
  digitalWrite(ledPin4, !hallPinState4);
  digitalWrite(ledPin5, !hallPinState5);

  delay(1);
}

*/

/*

//OPTION 3: bind 'em outside of loop' 
//NOTE: this proved to be way more complicated then I needed...

void pciSetup(byte pin) { 
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
 
// Use one Routine to handle each group
ISR (PCINT0_vect) {  // handle pin change interrupt for D8 to D13 here
  digitalWrite(13,digitalRead(8) and digitalRead(9));
  Serial.println("8 & 9");
}
 
ISR (PCINT1_vect) { // handle pin change interrupt for A0 to A5 here
  digitalWrite(13,digitalRead(A0));
}  
 
ISR (PCINT2_vect) { // handle pin change interrupt for D0 to D7 here
  int stateA = !digitalRead(6);
  int stateB = !digitalRead(7);
  digitalWrite(13,stateA);
  digitalWrite(12,stateA);
  Serial.println("\n "+String(stateA)+String(stateB)+" - "+!digitalRead(11));
}  
 
void setup() {  
int i;
 
// set pullups, if necessary
  for (i=0; i<=12; i++) digitalWrite(i,LOW);  // pinMode( ,INPUT) is default
  for (i=A0; i<=A5; i++) digitalWrite(i,LOW);
 
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);  // LED
  pinMode(13,OUTPUT);  // LED

  pciSetup(6);
  pciSetup(7);
  //pciSetup(8);
  //pciSetup(9);
  //pciSetup(A0);
  Serial.begin(9600);
}
 
 
void loop() {
  //Serial.println("delay"); delay(1000);
}

*/
