#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    24
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

const int transition = 1000; // milliseconds 
const int fps = 50;
const int stepDelay = transition/fps;

const int colors = 7;
const int rgb[colors][3] = { 
  {255,  0,  0}, 
  {255, 35, 0}, 
  {255, 100, 0},
  {0, 255,  0}, 
  {0, 0, 255}, 
  {170, 0, 100},
  {143, 0, 255}  
};

void setup() {
  Serial.begin(115200);
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {

  for (int i = 0; i < colors; i++) {
    int nextI = i == (colors-1) ? 0 : i+1;
    const float rStep = rgbStep(i,nextI,0);
    const float gStep = rgbStep(i,nextI,1);
    const float bStep = rgbStep(i,nextI,2);

    for (int j = 0; j < fps; j++) {
      int rSet = rgb[i][0] - (rStep*j);
      int gSet = rgb[i][1] - (gStep*j);
      int bSet = rgb[i][2] - (bStep*j);

      leds[0] = CRGB(rSet,gSet,bSet); 
      
      FastLED.show();
      delay(stepDelay);
    }

  }
  
}

float rgbStep(int i, int nextI, int rgbIndex) {
  float step = rgb[i][rgbIndex]-rgb[nextI][rgbIndex];
  step = step == 0 ? 0 : step/50;
  return step;
}
