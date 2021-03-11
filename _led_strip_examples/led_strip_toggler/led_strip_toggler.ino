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

struct sequence {
  String title;
  int duration;  
  void (*go)();
  int num;
};

#include "control/markers.h"
#include "sequences/niner_basic.h" 
#include "sequences/ping_pong.h" 
#include "sequences/color_palettes.h"
#include "sequences/pacifica.h"
#include "sequences/demo.h"
#include "sequences/fire.h"
#include "sequences/twinkle_fox.h"

const int sequencesLength = 16;

struct sequence sequences[sequencesLength] = { // WARNING, the name "marker_delay" is used programatically, so chaning it will make these weeds WACK, yo!
  {"marker_delay", 2000, marker_delay },{"niners_basic",    5*1000, niner_basic },
  {"marker_delay", 2000, marker_delay },{"ping_ping",       5*1000, ping_pong },
  {"marker_delay", 2000, marker_delay },{"twinkle_fox",     5*1000, fire_fly },
  {"marker_delay", 2000, marker_delay },{"color_palettes",  5*1000, color_palettes },
  {"marker_delay", 2000, marker_delay },{"pacifica",        5*1000, pacifica },
  {"marker_delay", 2000, marker_delay },{"demo",            5*1000, demo },
  {"marker_delay", 2000, marker_delay },{"fire",            5*1000, fire },
  {"marker_delay", 2000, marker_delay },{"twinkle_fox",     1*5*1000, twinkle_fox },
}; 

#include "control/control.h" 

void setup() {
  doSetup();
}

void loop() {
  sequences[current].go();
  checkSequenceChange();
}
