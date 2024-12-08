#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    50
#define BRT  255 // BRIGHTNESS 0-255
#define LED_TYPE    WS2812B // * LED String Strip Big: WS2811, Small string strip (Christmas light style): WS2812B 
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(10000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRT );
}

void loop() {
  // blink_up_and_back();
  // turn_input_number_on_off();
  rainbow_roll();
}


int LED_INDEX = 0;
int LAST_INDEX = 1;
int dir = -1;

void blink_up_and_back() {
  leds[LAST_INDEX] = CRGB(0,0,0);
  leds[LED_INDEX] = CRGB(100,100,100);
  FastLED.show();

  if (LED_INDEX >= NUM_LEDS - 1 || LED_INDEX <= 0) {
    dir = dir * -1;
  }
  LAST_INDEX = LED_INDEX;
  LED_INDEX = LED_INDEX + dir;
  delay(50);
}


int inputValue = 0;
bool ledStates[50];

void turn_input_number_on_off() {
  if (Serial.available() > 0) {
    inputValue = Serial.parseInt();
    if (inputValue >= 1 && inputValue <= 50) {
      Serial.print("Received valid input: "); Serial.println(inputValue);
      ledStates[inputValue] = ledStates[inputValue] == true ? false: true;
      if (ledStates[inputValue]) {
        leds[inputValue - 1] = CRGB(150,150,150);
      } else {
        leds[inputValue - 1] = CRGB(0,0,0);
      }
      FastLED.show();
    } 
  }
}


int maxB = 100;
float r = 0; 
float g = 0;
float b = 0;

float rSpd = 0.9; 
float gSpd = 0.6;
float bSpd = 0.3;

int rDir = 1;
int gDir = 1;
int bDir = 1;

void rainbow_roll() {
 for (int i = 0; i < NUM_LEDS; i++) {
    int g1 = int(g);
    leds[i] = CRGB(g1,r,b);
  }
  FastLED.show();
  r = r + (rSpd*rDir);
  if (r >= (maxB-rDir) || r <= 0) { rDir = rDir * -1; } 
  g = g + (gSpd*gDir);
  if (g >= (maxB-gDir) || g <= 0) { gDir = gDir * -1; } 
  b = b + (bSpd*bDir);
  if ( b > (maxB-bDir) || b <= 0 ) { bDir = bDir * -1; } 
  delay(20);
}

