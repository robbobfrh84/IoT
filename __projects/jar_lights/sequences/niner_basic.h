int rgb[3][3] = {
  {255,  0,  0},
  {255, 100, 0},
  {255, 225, 175},
};

int niner_basic_delay = 750;
int niner_basic_start = millis();

void niner_basic() {
  
  for (int i = 0; i < 3; i++) {
    if (millis() > niner_basic_delay + niner_basic_start) {
      for (int k = 0; k < NUM_LEDS; k+=2) {
        int n = (k+i) % 3;
        leds[k] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
        leds[k+1] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
      }
      niner_basic_start = millis();
    }
    FastLED.show();
  }

}