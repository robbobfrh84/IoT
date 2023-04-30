#include "ShiftIn.h"
#define FASTLED_ESP8266_RAW_PIN_ORDER
// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
// #define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>

#define NUM_LEDS 32
#define CHIPS 4

// const int ledStripPin = 7; 
#define ledStripPin D5

ShiftIn<CHIPS> shift;

CRGB ledStrip[NUM_LEDS];

void setup() {
  Serial.begin(9600); // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
  //shift.begin(8,9,10,11); 
  shift.begin(D1, D2, D3, D4);
  FastLED.addLeds<NEOPIXEL,ledStripPin>(ledStrip, NUM_LEDS); 
}

void displayValues() {
  int chipCnt = CHIPS * 8;
  int bitCnt = 0;
  for(int i = 0; i < shift.getDataWidth(); i++) { // print out all 8 buttons
    bitCnt++;
    if (i%8 == 0) {
      chipCnt -= 8;
      bitCnt = 0;
    }
    Serial.print( String(!shift.state(i)) ); // get state of button i
    if (!shift.state(i)) {
      ledStrip[bitCnt + chipCnt] = CRGB(40,0,40);
    } else {
      ledStrip[bitCnt + chipCnt] = CRGB(0,0,0);
    }
  }
  FastLED.show();
  Serial.println();
}

void loop() {
  if(shift.update()) { // read in all values. returns true if any button has changed
    displayValues();
  }
  delay(1);
}


// #include <FastLED.h>
// #define NUM_LEDS 24

// CRGB ledStrip[NUM_LEDS];

// const int ledStripPin = 7;
// const int selectPins[3] = {2, 3, 4}; 
// const int readPin = 5; 

// void setup() {
//   FastLED.addLeds<NEOPIXEL,ledStripPin>(ledStrip, NUM_LEDS); 
//   for (int i=0; i<3; i++) {
//     pinMode(selectPins[i], OUTPUT);
//     digitalWrite(selectPins[i], HIGH);
//   }
//   pinMode(readPin, INPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   FastLED.show();
//   for (byte pin=0; pin<=7; pin++) {
//     for (int i=0; i<3; i++) {
//       digitalWrite(selectPins[i], pin & (1<<i)?HIGH:LOW);
//     }
//     int connects = digitalRead(readPin);
//     if (!connects) {
//       ledStrip[pin] = CRGB(40,0,40);
//       ledStrip[pin+12] = CRGB(40,0,40);
//     } else {
//       ledStrip[pin] = CRGB(0,0,0);
//       ledStrip[pin+12] = CRGB(0,0,0);
//     }
//     // Serial.print(String(!connects));
//   }
//   //  Serial.println();
//   delay(1);

// }
