#include <SNESpaduino.h>

long int del = 3; //stepper delay. max 2,
int pos = 1; //stepper motor coil on location.
long int plungerLocation = 1260;//0mm - 76.2(most water), and dive.0-9600 steps
long int stepMove;
String packChar;  
bool doClear = true;
SNESpaduino pad(A0,A1,A2);
uint16_t btns;
bool doClearLeft = false;
bool doClearRight = false;


void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT); pinMode(4, OUTPUT); pinMode(5, OUTPUT); pinMode(6, OUTPUT);
  pinMode(10, OUTPUT); pinMode(11, OUTPUT); pinMode(12, OUTPUT);
  pinMode(7, OUTPUT); pinMode(8, OUTPUT); pinMode(9, OUTPUT);
  Serial.print("Plunger Location: ");Serial.print(plungerLocation/126);
  Serial.println(" mm");
}

void loop() {
  if (Serial.available()>0) {
    while (Serial.available()>0) {
      char digit = Serial.read();
      packChar += digit;
      delay(2);
    }
  }
  if (doClearLeft == true){ mclear("L");  doClearLeft = false;} 
  if (doClearRight == true){ mclear("R");  doClearRight = false;}  
 
  doClearLeft = true;
  doClearRight = true;

  

  if (pad.getButtons() & BTN_R) { 
    if (pad.getButtons() & BTN_RIGHT || pad.getButtons() & BTN_SELECT) { 
      RReverse(); doClearRight = false;
    } else {
    RForward(); doClearRight = false;
    }
  }
  
  if (pad.getButtons() & BTN_L) { doClearLeft = false;
    if (pad.getButtons() & BTN_LEFT) { 
      LReverse(); doClearRight = false;
    } else { doClearLeft = false;
      LForward(); 
    }
  }
  


  if (pad.getButtons() & BTN_UP) {
    plungerMove(1);
  }
  if (pad.getButtons() & BTN_DOWN) {
    plungerMove(-1);
  }
 
    

//  while (pad.getButtons() & BTN_R) {
//      if (pad.getButtons() & BTN_RIGHT) {
//        digitalWrite(12, HIGH); digitalWrite(10, HIGH); digitalWrite(11, LOW); //CCW
//        mclear("L");
//      } else if (pad.getButtons() & BTN_L) {
//        digitalWrite(9, HIGH); digitalWrite(8, LOW); digitalWrite(7, HIGH); //CW  
//      } else {
//        digitalWrite(12, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH); //CW
//        mclear("L");
//      }
//  }
//  
//  while (pad.getButtons() & BTN_L ) {
//    if (pad.getButtons() & BTN_LEFT ){
//      if (pad.getButtons() & BTN_R ){
//        digitalWrite(9, LOW); digitalWrite(8, HIGH); digitalWrite(7, HIGH); //CCW
//        digitalWrite(12, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH); //CW
//      } else { 
//        mclear("R");
//        digitalWrite(9, LOW); digitalWrite(8, HIGH); digitalWrite(7, HIGH); //CCW
//      }
//    } else if (pad.getButtons() & BTN_R){
//      if (pad.getButtons() & BTN_LEFT ){
//        digitalWrite(9, HIGH); digitalWrite(8, LOW); digitalWrite(7, HIGH); //CW
//        digitalWrite(12, HIGH); digitalWrite(10, HIGH); digitalWrite(11, LOW); //CW
//      } else { 
//        mclear("R");
//        //digitalWrite(9, HIGH); digitalWrite(8, HIGH); digitalWrite(7, LOW); //CCW
//        digitalWrite(12, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH); //CW
//      }
//    } else {
//      digitalWrite(9, HIGH); digitalWrite(8, LOW); digitalWrite(7, HIGH); //CW
//      mclear("R");
//    }
//  }
  
 
  if (packChar != ""){
    if (packChar[0] == 'R'){
      digitalWrite(12, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH); //CW
      delay(1000);
      digitalWrite(12, HIGH); digitalWrite(10, HIGH); digitalWrite(11, LOW); //CCW
      delay(1000);
      digitalWrite(12, LOW); digitalWrite(10, LOW); digitalWrite(11, LOW); //OFF
      digitalWrite(9, LOW); digitalWrite(8, HIGH); digitalWrite(7, HIGH); //CW
      delay(1000);
      digitalWrite(9, HIGH); digitalWrite(8, LOW); digitalWrite(7, HIGH); //CCW
      delay(1000);
      digitalWrite(9, LOW); digitalWrite(8, LOW); digitalWrite(7, LOW); //OFF
      packChar = String();
      

    } else {
      int order = (packChar.toInt() * 126) - plungerLocation;
      plungerLocation = packChar.toInt() * 126;
      Serial.print("Plunger Location: ");Serial.print(plungerLocation/126);
      Serial.println(" mm");
      Serial.print("Steps to move: ");Serial.println(order);
      plungerMove(order);
      packChar = String();
    }  
  }  
}

int mclear(String motor){
  if (motor == "R"){
     digitalWrite(12, LOW); digitalWrite(10, LOW); digitalWrite(11, LOW); //OFF
  }
  if (motor == "L"){
    digitalWrite(9, LOW); digitalWrite(8, LOW); digitalWrite(7, LOW); //OFF
  }
}


void RForward(){ digitalWrite(12, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH);}
void RReverse(){ digitalWrite(12, HIGH); digitalWrite(10, HIGH); digitalWrite(11, LOW);} 

void LForward(){ digitalWrite(9, HIGH);   digitalWrite(8, LOW);   digitalWrite(7, HIGH);}
void LReverse(){ digitalWrite(9, LOW);   digitalWrite(8, HIGH);   digitalWrite(7, HIGH);}




int plungerMove(int dist){
  if (dist > 0){
    for (int i = 0; i < dist; i++){
      doubleStep(pos); 
      pos+=1; if (pos > 4 ){pos = 1;}
    }
  }
  if (dist < 0){
    for (int i = 0; i < abs(dist); i++){ //backward
      pos-=1; if (pos < 1) {pos = 4;}//backward
      doubleStep(pos);  
    }
  }  
}

int doubleStep(int pos){
  if (pos == 1){ digitalWrite(3, LOW); digitalWrite(4, LOW); 
                 digitalWrite(5, HIGH); digitalWrite(6, HIGH); delay(del);}
  if (pos == 2){ digitalWrite(3, HIGH); digitalWrite(4, LOW); 
                 digitalWrite(5, LOW); digitalWrite(6, HIGH); delay(del);}
  if (pos == 3){ digitalWrite(3, HIGH); digitalWrite(4, HIGH); 
                 digitalWrite(5, LOW); digitalWrite(6, LOW); delay(del);}
  if (pos == 4){ digitalWrite(3, LOW); digitalWrite(4, HIGH); 
                 digitalWrite(5, HIGH); digitalWrite(6, LOW); delay(del);}
}
