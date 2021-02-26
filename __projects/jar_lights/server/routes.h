void handleLed(String key, String value);
void handleCustom(String value);
void handleSequence(String value);
void handleLock(String value);
void handlePage(String page);

bool validReq = false;
bool returnData = false;

void API() {
  setCrossOrigin();
  data["lock"] = lock;
  data["current_sequence"] = current_sequence;
  data["sequence_index"] = sequence_index;
  data["your_req"] = "api";
  data["show_sequence"] = showSequence;
  buf(data);
}

void API_query() {
  indicatorBlue();
  Serial.println("\n/?");
  setCrossOrigin();
  validReq = false;
  returnData = false;
  data["your_req"] = "";
  DynamicJsonDocument tempData(512);

  for (int i = 0; i < server.args(); i++) {
    String key = server.argName(i);
    String value = server.arg(i);
    Serial.println("key: "+key+", value: "+value);
    
    if (key.toInt() > 0 && key.toInt() <= NUM_LEDS) { handleLed( key, value ); } 
    else if (key == "req" && value == "custom") { handleCustom( value ); } 
    else if (key == "sequence") { handleSequence(value); } 
    else if (key == "lock") { handleLock(value); } 
    else if (key == "page") { handlePage(value); } 
    else {
      Serial.println("!!! unknown key/value pair !!!");
    }
  }; 

  if (validReq) {
    if (data["your_req"] == "custom") {
      updateStrip();
      tempData["message"] = "Successfully updated LED(s) request";
      buf(tempData);
    } else if (returnData) {
      buf(data);
    } else {
      tempData["message"] = "Request is valid and processed! Just no specific response though, sorry.";
      buf(tempData);
    }
  } else {
    tempData["message"] = "We got your message. But there's something wrong with at least one of your keys and/or values.... Sorry, I can't tell you anything more... :-(";
    buf(tempData);
  }

  indicatorGreen();  
};

void handleLed(String key, String value) {
  validReq = true;
  data[key] = value;
}

void handleCustom(String value) {
  validReq = true;
  showSequence = false;
  data["show_sequence"] = showSequence;
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  data["your_req"] = value;   
}

void handleSequence(String value) {
  sequence_index = value.toInt()-2;
  if (lock) {
    sequence_index = value.toInt()-1;
    lockBlinks(value.toInt()+1,300,sequences[sequence_index].title);
  } 
  showSequence = true;
  validReq = true;
  returnData = true;
  changeSequence();
  data["show_sequence"] = showSequence;
  data["current_sequence"] = current_sequence;
  data["sequence_index"] = sequence_index;
  data["lock"] = lock;
  data["your_req"] = "sequence="+value;
}

void handleLock(String value) {
  if (value == "true") {
    lock = true; 
  } else {
    lock = false; 
  }
}

void handlePage(String page) {
  validReq = true;
  returnData = true;
  data["lock"] = lock;
  data["current_sequence"] = current_sequence;
  data["sequence_index"] = sequence_index;
  data["your_req"] = "page="+page;
  if (page == "custom") {
    showSequence = false;
    data["show_sequence"] = showSequence;
    changeSequence();
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  } else {
    showSequence = true;
    data["show_sequence"] = showSequence;
    sequence_index = sequence_index-2;
    changeSequence();
  }
}




