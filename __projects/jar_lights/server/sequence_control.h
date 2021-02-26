bool btnUp = true;
bool lock = false;
int sequenceStart = millis();

void lockBlink(int r, int g, int b, int count, int time, String title);
void lockBlinks(int count, int time, String title);

void changeSequence() {
  if (sequence_index < sequencesLength - 1) {
    sequence_index++;
  } else {
    sequence_index = 0;  
  }
  current_sequence = sequences[sequence_index].title;
  if (
    sequences[sequence_index].title == "twinkle_fox"
    ||
    sequences[sequence_index].title == "fire_fly"
  ) {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(aleds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  } else {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  }
  sequenceStart = millis();
}

void checkButtonHold() {
  bool hold = true;
  int wait = 2000;
  int start = millis();
  while (millis() < wait + start) { 
    if (!digitalRead(toggleBtn)) {
      hold = false;
      break;
    }
    delay(30);
  }
  if (hold) {
    int count = sequence_index+1;
    if (sequences[sequence_index].title == "marker_delay") {
      count = sequence_index+2;
    }
    int sendCount = count;
    if (sendCount > sequencesLength - 2) {
      sendCount = sequencesLength;
    }
    lockBlinks(sendCount,300,sequences[sequence_index].title);
    sequence_index = count - 2;
    changeSequence();
    lock = !lock;
  }
}  

void checkToggleBtn() {
  if (digitalRead(toggleBtn)) {
    indicatorBlue();
    checkButtonHold();
    if (!lock) {
      if (btnUp) {
        changeSequence();
      }
      btnUp = false;
      sequenceStart = millis();
    }
    if (!showSequence) {
      showSequence = true;
    }
    delay(30); 
  } else {
    indicatorGreen();
    btnUp = true;
  }
}

void checkSequenceChange() {
  if (!lock) {
    if (millis() > sequenceStart + sequences[sequence_index].duration) {
      changeSequence();
    }
  }
  checkToggleBtn();
}

void lockBlink(int r, int g, int b, int count, int time, String title) {
  FastLED.clear();
  for (int i = 0; i < count; i++) {
    leds[i] = CRGB(r,g,b);
  }
  FastLED.show();
  delay(time);
}

void lockBlinks(int count, int time, String title) {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // NOTE: we first turn the FastLED to single RGB because the blink is always single. But, we have to ask if the followin sequence is RGB array or not and swap back if so.
  lockBlink(255,255,255,NUM_LEDS,time,title);
  lockBlink(255,0,255,count,time,title);
  lockBlink(255,255,255,NUM_LEDS,time,title);
  lockBlink(255,0,255,count,300,title);
  lockBlink(255,255,255,NUM_LEDS,time,title);
  lockBlink(255,0,255,count,300,title);
  if (
    sequences[sequence_index].title == "twinkle_fox"
    ||
    sequences[sequence_index].title == "fire_fly"
  ) {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(aleds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  } else {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  }
}

