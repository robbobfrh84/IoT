bool btnUp = true;

void changeSequence() {
  if(current < sequencesLength - 1) {
    current++;
  } else {
    current = 0;  
  }
  currentTitle = sequences[current].title;
  if (sequences[current].title == "twinkle_fox") {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(aleds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  } else {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  }
}

void checkToggleBtn() {
  bool btnState = digitalRead(toggleBtn);
  if (digitalRead(toggleBtn)) {
    digitalWrite(indicatorLight, LOW);
    if (btnUp) {
      changeSequence();
    }
    btnUp = false;
    sequenceStart = millis();
    delay(30); 
  } else {
    digitalWrite(indicatorLight, HIGH);
    btnUp = true;
  }
}

void checkSequenceChange() {
  if (millis() > sequenceStart + sequences[current].duration) {
    changeSequence();
    sequenceStart = millis();
  }
  checkToggleBtn();
}
