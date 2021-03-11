  // WARNING: the order of the declarations here are sensative!
#include <FastLED.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

#define LED_PIN     12 // 12 - ADAFRUIT HUZZAH FEATHER | 2 - NODE MCU
#define NUM_LEDS    24
#define BRIGHTNESS  255 // 0-255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB // some strips are GRB

DynamicJsonDocument data(2048);
CRGBArray<NUM_LEDS> aleds; // Special for Twinkle_fox
CRGB leds[NUM_LEDS];

const int indicatorR = 15; // 15 - ADAFRUIT HUZZAH FEATHER | 1 - NODE MCU
const int indicatorG = 13; // 13 - ADAFRUIT HUZZAH FEATHER | 3 - NODE MCU
const int indicatorB = 0; // 0 - ADAFRUIT HUZZAH FEATHER | 15 - NODE MCU

const int toggleBtn = 14;  // 14 - ADAFRUIT HUZZAH FEATHER | ? - NODE MCU

int sequence_index = 0;
String current_sequence;
bool showSequence = true;

bool wifiConnected = false; 
unsigned long timeTrack;

struct sequence {
  String title;
  int duration;
  void (*go)();
};

const int sequencesLength = 16;

#include "sequences/marker_delay.h"
#include "sequences/niner_basic.h"
#include "sequences/ping_pong.h"
#include "sequences/color_palettes.h"
#include "sequences/pacifica.h"
#include "sequences/demo.h"
#include "sequences/fire.h"
#include "sequences/twinkle_fox.h"

struct sequence sequences[sequencesLength] = { // WARNING, the name "marker_delay" is used programatically, so chaning it will make these weeds WACK, yo!
  {"marker_delay", 2000, marker_delay },{"niners_basic",    5*60*1000, niner_basic },
  {"marker_delay", 2000, marker_delay },{"ping_ping",       5*60*1000, ping_pong },
  {"marker_delay", 2000, marker_delay },{"fire_fly",        5*60*1000, fire_fly },
  {"marker_delay", 2000, marker_delay },{"color_palettes",  5*60*1000, color_palettes },
  {"marker_delay", 2000, marker_delay },{"pacifica",        5*60*1000, pacifica },
  {"marker_delay", 2000, marker_delay },{"fire",          5*60*1000, fire },
  {"marker_delay", 2000, marker_delay },{"demo",            15*60*1000, demo },
  {"marker_delay", 2000, marker_delay },{"twinkle_fox",     15*60*1000, twinkle_fox },
};

#include "server/helpers.h"
#include "server/wifi.h"
#include "server/sequence_control.h"
#include "server/routes.h"

void setup(void) {
  Serial.begin(115200);
  pinMode(indicatorR, OUTPUT);
  pinMode(indicatorG, OUTPUT);
  pinMode(indicatorB, OUTPUT);
  pinMode(toggleBtn, INPUT);
  indicatorYellow();
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  chooseNextColorPalette(gTargetPalette);
  FAIRYchooseNextColorPalette(gTargetPalette);
  current_sequence = sequences[sequence_index].title;
  delay(1000);
  sequenceStart = millis();
  setupWifi();
  dataSetup();
  if (wifiConnected) {
    server.onNotFound([]() {
      if (!handleFileRead(server.uri()))
        server.send(404, "text/plain", "404: Not Found");
    });
    server.on("/q", API_query);
    server.on("/api", API);
    startWifi();
  }
}

void loop(void) {
  if (wifiConnected) {
    listenWifi();
  } 
  if (showSequence) {
    sequences[sequence_index].go();
  }
  checkSequenceChange();
}
