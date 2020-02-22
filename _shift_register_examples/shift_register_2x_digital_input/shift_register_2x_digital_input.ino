#include "ShiftIn.h"

ShiftIn<2> shift;

void setup() {
  Serial.begin(9600); // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
  shift.begin(8, 9, 11, 12);
}

void displayValues() {
  for(int i = 0; i < shift.getDataWidth(); i++) { // print out all 8 buttons
    Serial.print( !shift.state(i) ); // get state of button i
  }
  Serial.println();
}

void loop() {
  if(shift.update()) { // read in all values. returns true if any button has changed
    displayValues();
  }
  delay(1);
}

// - - - - -TESTING FOR THREE!

//#include "ShiftIn.h"
//
//ShiftIn<3> shift;
//
//void setup() {
//  Serial.begin(9600); // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
//  shift.begin(8, 9, 11, 12);
//}
//
//void displayValues() {
//  for(int i = 0; i < shift.getDataWidth(); i++) { // print out all 8 buttons
//    Serial.print( !shift.state(i) ); // get state of button i
//  }
//  Serial.println();
//}
//
//void loop() {
//  if(shift.update()) { // read in all values. returns true if any button has changed
//    displayValues();
//  }
//  delay(1);
//}
