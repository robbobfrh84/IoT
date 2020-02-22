#include <FastLED.h>
#define NUM_LEDS 24

CRGB ledStrip[NUM_LEDS];

const int ledStripPin = 7;
const int selectPins[3] = {2, 3, 4}; 
const int readPin = 5; 

void setup() {
  FastLED.addLeds<NEOPIXEL,ledStripPin>(ledStrip, NUM_LEDS); 
  for (int i=0; i<3; i++) {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  FastLED.show();
  for (byte pin=0; pin<=7; pin++) {
    for (int i=0; i<3; i++) {
      digitalWrite(selectPins[i], pin & (1<<i)?HIGH:LOW);
    }
    int connects = digitalRead(readPin);
    if (!connects) {
      ledStrip[pin] = CRGB(40,0,40);
      ledStrip[pin+12] = CRGB(40,0,40);
    } else {
      ledStrip[pin] = CRGB(0,0,0);
      ledStrip[pin+12] = CRGB(0,0,0);
    }
    // Serial.print(String(!connects));
  }
  //  Serial.println();
  delay(1);

}
