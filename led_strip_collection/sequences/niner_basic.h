int rgb[3][3] = {
  {255,  0,  0},
  {255, 100, 0},
  {255, 225, 175},
};

void niner_basic() {
  
  for (int i = 0; i < 3; i++) {
    for (int k = 0; k < NUM_LEDS; k+=2) {
      int n = (k+i) % 3;
      leds[k] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
      leds[k+1] = CRGB(rgb[n][0],rgb[n][1],rgb[n][2]);
    }
    FastLED.show();
    int wait = 750;
    int now = millis();
    while (millis() < wait + now) { 
      checkToggleBtn();
      delay(10);
      if (currentTitle != "niners_basic") { return; }
    }
  }
}
