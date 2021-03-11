void doSetup() {
  pinMode(toggleBtn, INPUT);
  pinMode(indicatorLight, OUTPUT);
  //Serial.begin(115200);
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  chooseNextColorPalette(gTargetPalette);
  FAIRYchooseNextColorPalette(gTargetPalette);
  digitalWrite(indicatorLight, HIGH);
  currentTitle = sequences[current].title;
  delay(1000);
  sequenceStart = millis();
}
