DynamicJsonDocument rgbArr(String value) {
  DynamicJsonDocument rgb(512);
  String line = value;
  int split = line.indexOf(",");
  rgb["r"] = line.substring(0, split);
  String bg = line.substring(split+1, line.length());
  int split2 = bg.indexOf(",");
  rgb["g"] = bg.substring(0, split2);
  rgb["b"] = bg.substring(split2+1, bg.length());
  return rgb;
}

void updateStrip() {
  FastLED.clear();
  for (int i = 0; i <= NUM_LEDS; i++) {
    DynamicJsonDocument cols(215); 
    String value = data[String(i)];
    cols = rgbArr(value);
    leds[i-1] = CRGB(cols["r"],cols["g"],cols["b"]);
  }
  FastLED.show();
}

void dataSetup() {
  data["NUM_LEDS"] = NUM_LEDS;
  data["current_sequence"] = current_sequence; 
  data["sequence_index"] = sequence_index; 
  for (int i=0; i<NUM_LEDS; i++) {
    data[String(i+1)] = "0,0,0";
    updateStrip();
  }
  for (int i = 0; i < sequencesLength; i++) {
    data["sequences"][i]["index"] = i;
    data["sequences"][i]["title"] = sequences[i].title;
    data["sequences"][i]["duration"] = sequences[i].duration;
  }
}

void indicatorRed() {
  digitalWrite(indicatorR, LOW);
  digitalWrite(indicatorG, HIGH);
  digitalWrite(indicatorB, HIGH);
}

void indicatorGreen() {
  digitalWrite(indicatorR, HIGH);
  digitalWrite(indicatorG, LOW);
  digitalWrite(indicatorB, HIGH);
}

void indicatorBlue() {
  digitalWrite(indicatorR, HIGH);
  digitalWrite(indicatorG, HIGH);
  digitalWrite(indicatorB, LOW);
}

void indicatorYellow() {
  analogWrite(indicatorR, 34);
  analogWrite(indicatorG, 100);
  digitalWrite(indicatorB, LOW);
}

void indicatorOff() {
  digitalWrite(indicatorR, HIGH);
  digitalWrite(indicatorG, HIGH);
  digitalWrite(indicatorB, HIGH);
}