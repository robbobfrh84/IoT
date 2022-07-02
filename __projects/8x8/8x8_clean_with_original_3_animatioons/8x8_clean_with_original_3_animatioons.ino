#include <Adafruit_NeoPixel.h>
#define PIN        6 
#define NUMPIXELS 64 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include "retroWipe.h"
#include "rainbowWormHole.h"
#include "pixDance.h"
#include "bluePixelWondersThroughHell.h"


#include <WiFi101.h> // YOU NEED THIS > NO CLUE why!? WiFi module MUST do something that makes it so it doesn't flicker. You could open the module to try and find out. NOTE: you're not connecting to wifi, just useing whatever i uses to work better!

void setup() {
  pixels.begin();
  WiFi.begin("dummy", "dummy"); // YOU NEED THIS! See note above line "#include <WiFi101.h>"
}

void loop() {
  
  retroWipe();
  rainbowWormHole(1 * 60 * 1000);  // mins far left

  retroWipe();
  pixDance(5 * 60 * 1000); // mins far left

  retroWipe();
  bluePixelWondersThroughHell(1 * 60 * 1000);  // mins far left
  
}
