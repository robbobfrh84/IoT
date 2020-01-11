#include <FastLED.h>

#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

int* cols[3];
int red[3] = {255, 0, 0}; 
int gold[3] = {255, 100, 0}; 
int white[3] = {255, 225, 175};

int* ar[2];
int ar1[] = {1,2, 3};
int ar2[] = {5, 6, 7, 8, 9, 10};


void setup() { 
  FastLED.addLeds<NEOPIXEL,12>(leds, NUM_LEDS); 
  Serial.begin(9600);
  cols[0] = red;
  cols[1] = gold;
  cols[2] = white;

}

void loop(){ 
  
  for(int i = 0; i < 3; i++) { 

    leds[0] = CRGB(cols[0][0],cols[0][1],cols[0][2]);
    leds[1] = CRGB(cols[0][0],cols[0][1],cols[0][2]);
    leds[2] = CRGB(cols[1][0],cols[1][1],cols[1][2]);
    leds[3] = CRGB(cols[1][0],cols[1][1],cols[1][2]);
    leds[4] = CRGB(cols[2][0],cols[2][1],cols[2][2]);
    leds[5] = CRGB(cols[2][0],cols[2][1],cols[2][2]);

    leds[11] = CRGB(cols[0][0],cols[0][1],cols[0][2]);
    leds[10] = CRGB(cols[0][0],cols[0][1],cols[0][2]);
    leds[9] = CRGB(cols[1][0],cols[1][1],cols[1][2]);
    leds[8] = CRGB(cols[1][0],cols[1][1],cols[1][2]);
    leds[7] = CRGB(cols[2][0],cols[2][1],cols[2][2]);
    leds[6] = CRGB(cols[2][0],cols[2][1],cols[2][2]);
    
    int temp = cols[0], j; 
    for (j = 0; j < 2; j++) {
      cols[j] = cols[j + 1]; 
    }
    cols[j] = temp; 

    FastLED.show();
    delay(500);
    
  }

}
