int led = 13; // represents "000" state.
String c = ""; // [c]urrent button
int buttonA = 2;
int buttonB = 3;
int buttonC = 4;


void setup() {
  Serial.begin(9200);
  pinMode(led, OUTPUT);     
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
}

void loop() {
  int stateA = digitalRead(buttonA);
  int stateB = digitalRead(buttonB);
  int stateC = digitalRead(buttonC);
  String bc = ""; // [b]utton [c]ode
  bc += String(stateA)+String(stateB)+String(stateC);

  digitalWrite(led, 0);  
  if      (bc == "100") { if (c != "1") { c = "1"; Serial.println(bc+" = 1"); } }
  else if (bc == "010") { if (c != "2") { c = "2"; Serial.println(bc+" = 2"); } }
  else if (bc == "001") { if (c != "3") { c = "3"; Serial.println(bc+" = 3"); } }
  else if (bc == "110") { if (c != "4") { c = "4"; Serial.println(bc+" = 4"); } }
  else if (bc == "101") { if (c != "5") { c = "5"; Serial.println(bc+" = 5"); } }
  else if (bc == "011") { if (c != "6") { c = "6"; Serial.println(bc+" = 6"); } }
  else if (bc == "111") { if (c != "7") { c = "7"; Serial.println(bc+" = 7"); } }
  else { c = "";  digitalWrite(led, 1); } // bc == "000"
    
  delay(1);    
}
