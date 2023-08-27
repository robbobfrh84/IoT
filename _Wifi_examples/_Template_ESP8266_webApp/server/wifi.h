void setupWifi() {
  const char* ssid = wifiJSON["name"]; 
  const char* password = wifiJSON["pass"];
  IPAddress local_IP(wifiJSON["ip"][0], wifiJSON["ip"][1], wifiJSON["ip"][2], wifiJSON["ip"][3]); 
  IPAddress gateway(wifiJSON["gateway"][0], wifiJSON["gateway"][1], wifiJSON["gateway"][2], wifiJSON["gateway"][3]); 
  IPAddress subnet(wifiJSON["subnet"][0], wifiJSON["subnet"][1], wifiJSON["subnet"][2], wifiJSON["subnet"][3]);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  delay(10);
  Serial.println('\n');
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  
  Serial.println("Connecting ...");
  long waitForWifi = 20000;
  long startTime = millis();
  while ((WiFi.status() != WL_CONNECTED) && (millis() - startTime < waitForWifi)) {
    delay(250);
    String delayed = String(millis() - startTime);
    Serial.print("Waiting for Wifi ("+String(waitForWifi)); Serial.println(" ms): "+delayed);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("\nWiFi.status(): ");
    Serial.println(WiFi.status()); // * see readme for status code docs
  } else {
    wifiConnected = true;
    Serial.println("Connected to "); Serial.println(WiFi.SSID());
    Serial.print("IP address:\t"); Serial.println(WiFi.localIP());
    if (MDNS.begin("esp8266")) {
      Serial.println("mDNS responder started");
    } else {
      Serial.println("Error setting up MDNS responder!");
    }
  }
}

void startWifi() {
  if (wifiConnected) { 
    server.onNotFound([]() { // * serve default /index.html page.                      
      if (!handleFileRead(server.uri())) {
        server.send(404, "text/plain", "404: Not Found"); 
      }               
    });
    server.on("/q", API_query); 
    server.begin();
    Serial.println("HTTP server started");
  }
}

void listenWifi(void) {
  server.handleClient();
}