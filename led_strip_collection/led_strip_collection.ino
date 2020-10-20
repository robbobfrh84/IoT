#include <FastLED.h>
#define LED_PIN     12
#define NUM_LEDS    24
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGBArray<NUM_LEDS> aleds; // Special for Twinkle_fox
CRGB leds[NUM_LEDS];

int indicatorLight = 13;
int toggleBtn = 14;

int current = 0; // starting sequence. 
String currentTitle;
int sequenceStart = millis();
void checkToggleBtn();

struct sequence {
  String title;
  int duration;  
  void (*go)();
  int num;
};

#include "control/marker_delay.h"
#include "sequences/niner_basic.h" 
#include "sequences/ping_pong.h" 
#include "sequences/color_palettes.h"
#include "sequences/pacifica.h"
#include "sequences/demo.h"
#include "sequences/fire.h"
#include "sequences/twinkle_fox.h"

const int sequencesLength = 16;
struct sequence sequences[sequencesLength] = {
  {"marker_delay", 2000, marker_delay },
  {"niners_basic", 60*1000, niner_basic },
  
  {"marker_delay", 2000, marker_delay },
  {"ping_ping", 60*1000, ping_pong },

  {"marker_delay", 2000, marker_delay },
  {"twinkle_fox", 60*1000, fire_fly },
  
  {"marker_delay", 2000, marker_delay },
  {"color_palettes", 60*1000, color_palettes },

  {"marker_delay", 2000, marker_delay },
  {"pacifica", 60*1000, pacifica },

  {"marker_delay", 2000, marker_delay },
  {"demo", 60*1000, demo },

  {"marker_delay", 2000, marker_delay },
  {"fire", 60*1000, fire },

  {"marker_delay", 2000, marker_delay },
  {"twinkle_fox", 5*60*1000, twinkle_fox },
}; 

#include "control/control.h" 

void setup() {
  pinMode(toggleBtn, INPUT);
  pinMode(indicatorLight, OUTPUT);
  //Serial.begin(115200);
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  chooseNextColorPalette(gTargetPalette);
  FAIRYchooseNextColorPalette(gTargetPalette);
  digitalWrite(indicatorLight, HIGH);
  currentTitle = sequences[current].title;
  delay(1000);
  sequenceStart = millis();
}

void loop() {
  sequences[current].go();
  checkSequenceChange();
}
