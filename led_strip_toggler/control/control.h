bool btnUp = true;
bool lock = false;
int sequenceStart = millis();

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

void checkButtonHold() {
  bool hold = true;
  int wait = 2000;
  int start = millis();
  while (millis() < wait + start) { 
    if (!digitalRead(toggleBtn)) {
      hold = false;
      Serial.println("! break");
      break;
    }
    delay(30);
  }
  if (hold) {
    int count = current+1;
    String title = sequences[current].title;
    if (sequences[current].title == "marker_delay") {
      count = current+2;
    }
    LockBlink(255,255,255,NUM_LEDS,500,title);
    LockBlink(255,0,255,count,500,title);
    LockBlink(255,255,255,NUM_LEDS,500,title);
    LockBlink(255,0,255,count,500,title);
    current = count - 2;
    changeSequence();
    lock = !lock;
  }
}  

void checkToggleBtn() {
  if (digitalRead(toggleBtn)) {
    digitalWrite(indicatorLight, LOW);
    checkButtonHold();
    if (!lock) {
      if (btnUp) {
        changeSequence();
      }
      btnUp = false;
      sequenceStart = millis();
    }
    delay(30); 
  } else {
    digitalWrite(indicatorLight, HIGH);
    btnUp = true;
  }
}

void checkSequenceChange() {
  if (!lock) {
    if (millis() > sequenceStart + sequences[current].duration) {
      changeSequence();
      sequenceStart = millis();
    }
  }
  checkToggleBtn();
}
