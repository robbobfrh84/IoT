#include <Adafruit_NeoPixel.h>
#define PIN        6 
#define NUMPIXELS 64 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/* included local files...*/
#include "toolkit.h"
#include "_colors.h"

#include "retroWipe.h"
#include "rainbowWormHole.h"
#include "pixDance.h"
#include "bluePixelWondersThroughHell.h"
#include "purpleRain.h"

#include "_8x8_stills.h"


#include <WiFi101.h> // YOU NEED THIS > NO CLUE why!? WiFi module MUST do something that makes it so it doesn't flicker. You could open the module to try and find out. NOTE: you're not connecting to wifi, just useing whatever i uses to work better!
void setup() {
  pixels.begin();
  WiFi.begin("dummy", "dummy"); // YOU NEED THIS! See note above line "#include <WiFi101.h>"
  retroWipe(); 
}


void loop() {
  
  rainbowWormHole(1 * 60 * 1000);               retroWipe(); 
  pixDance(1 * 60 * 1000);                      retroWipe(); 
  purpleRain(1 * 60 * 1000);                    retroWipe(); 
  bluePixelWondersThroughHell(1 * 60 * 1000);   retroWipe(); 

  _8x8_stills("swatch", (1 * 15 * 1000) );       retroWipe(); 
  _8x8_stills("bob", (1 * 15 * 1000) );       retroWipe(); 
  
}
