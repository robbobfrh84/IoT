#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    3
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2812B // * LED String Strip Big: WS2811, Small string strip (Christmas light style): WS2812B 
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

int rgb[3][3] = { 
  { 255, 0,   0   },
  { 0,   255, 0   }, 
  { 0,   0,   255 } 
};

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  
  leds[0] = CRGB(rgb[0][0],rgb[0][1],rgb[0][2]); 
  FastLED.show();
  delay(1000);
  
  leds[1] = CRGB(rgb[1][0],rgb[1][1],rgb[1][2]);
  FastLED.show();
  delay(1000);

  leds[2] = CRGB(rgb[2][0],rgb[2][1],rgb[2][2]);
  FastLED.show();
  delay(1000);


  /* TURN OFF */
  leds[0] = CRGB(0,0,0); 
  leds[1] = CRGB(0,0,0); 
  leds[2] = CRGB(0,0,0); 

  FastLED.show();
  delay(1000);

}
