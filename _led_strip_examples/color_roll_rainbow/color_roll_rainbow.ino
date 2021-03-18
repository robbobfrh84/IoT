#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    7
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

const int transition = 1000; // milliseconds 
const int fps = 50;
const int stepDelay = transition/fps;
int cnt = 0;

const int colors = 7;
const int rgb[colors][3] = { 
  {255,  0,  0}, 
  {255, 50, 0}, 
  {255, 100, 0},
  {0, 255,  0}, 
  {0, 0, 255}, 
  {170, 0, 100},
  {143, 0, 255}  
};
int rgbT[colors][3];

void setup() {
  // Serial.begin(115200); // Development only
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  for (int t = 0; t < colors; t++) {
    int nextI = (t+1) % colors;
    rgbT[t][0] = rgbStep(t,nextI,0);
    rgbT[t][1] = rgbStep(t,nextI,1);
    rgbT[t][2] = rgbStep(t,nextI,2);
  }
}

void loop() {
  
  for (int f = 0; f < fps; f++) {

    for (int k = 0; k < NUM_LEDS; k++) {
      int nextI = (k+cnt+1) % colors;
      int rSet = rgb[nextI][0] - (rgbT[nextI][0]*f);
      int gSet = rgb[nextI][1] - (rgbT[nextI][1]*f);
      int bSet = rgb[nextI][2] - (rgbT[nextI][2]*f);
      leds[k] = CRGB(rSet,gSet,bSet); 
    }
    
    FastLED.show();
    delay(stepDelay);
  }

  cnt = cnt == colors - 1 ? 0 : cnt+1;

}

float rgbStep(int i, int nextI, int rgbIndex) {
  float step = rgb[i][rgbIndex]-rgb[nextI][rgbIndex];
  step = step == 0 ? 0 : step/50;
  return step;
}
