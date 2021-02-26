#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    32
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int blue = 0;
float blueFloat = 0.0;
float blueSpeed = -0.5;

int const redArrSize = 5;
int red[redArrSize] = {4,5,6,7,8};
int redColor[redArrSize] = {10,20,30,80,255};
int redDir[redArrSize] = {1,1,1,1,1};
int redSpeed = 1;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  FastLED.clear();  // clear all pixel data
  moveRed();
  moveBlue(); 
  FastLED.show();
  delay(30);
}

void moveRed() {
  for (int r = 0; r < redArrSize; r++) {
    if (red[r] >= NUM_LEDS-1 || red[r] <= 0) {
      redDir[r] *= -1;
    } 
    int led = red[r];
    leds[led] = CRGB(redColor[r],0,0);
    red[r] += redDir[r];
  }
}

void moveBlue() {
  if (blueFloat >= NUM_LEDS-1 || blueFloat <= 0) {
    blueSpeed = (float)(blueSpeed*-1.0);
  } 
  leds[blue] = CRGB(0,255,0);
  blueFloat = (float)(blueFloat+blueSpeed);
  blue = blueFloat;
}
