void marker_delay() {
  FastLED.clear();
  for (int i = 0; i < current+2; i++) {
    leds[i] = CRGB(255,0,255);
  }
  FastLED.show();
}

void LockBlink(int r, int g, int b, int count, int time, String title) {
  FastLED.clear();
  for (int i = 0; i < count; i++) {
    if (title == "twinkle_fox") {
      aleds[i] = CRGB(r,g,b);
    } else {
      leds[i] = CRGB(r,g,b);
    }
  }
  FastLED.show();
  delay(time);
}
