void setCrossOrigin() {
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

void buf(DynamicJsonDocument obj) {
  String bufs;
  serializeJson(obj, bufs);
  server.send(200, "application/json", bufs);
}

String getContentType(String filename) {
  if (filename.endsWith(".html"))       { return "text/html"; }
  else if (filename.endsWith(".css"))   { return "text/css"; }
  else if (filename.endsWith(".js"))    { return "application/javascript"; }
  else if (filename.endsWith(".ico"))   { return "image/x-icon"; }
  return "text/plain";
}

bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  String contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}

void get_Wifi_Config() {
  File file = SPIFFS.open(wifiConfig, "r");
  String lines;
  if (!file) {
    Serial.println("\nFile not found :(");
  } else {
    while(file.available()) {
      lines += file.readStringUntil('\n');
    } 
    file.close();
  }
  deserializeJson(wifiJSON, lines);
}