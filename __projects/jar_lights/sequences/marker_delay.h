void marker_delay() {
  FastLED.clear();
  for (int i = 0; i < sequence_index+2; i++) {
    leds[i] = CRGB(255,0,255);
  }
  FastLED.show();
}