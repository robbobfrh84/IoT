// NOTE: Positive pin uses usb on esp8266. usb pin is 5v. the 3v works, but it's recommened to not use it because it'll only work for a few leds. 
#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    24
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int rgb[3][3] = {
  {255,  0,  0},
  {255, 100, 0},
  {255, 225, 175},
};

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  for (int i = 0; i < 3; i++) {
    for (int k = 0; k < NUM_LEDS; k+=2) {
      int n = (k+i) % 3;
      leds[k] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
      leds[k+1] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
    }
    FastLED.show();
    delay(750);
  }
}
