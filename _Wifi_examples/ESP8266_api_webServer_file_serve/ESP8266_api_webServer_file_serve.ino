bool wifiConnected = false; 
#include "server/routes.h"; // NOTE: server/wifi.h is included in server/routes.h

void setup(void) {
  Serial.begin(115200);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  setupWifi();
  if (wifiConnected) {
    server.onNotFound([]() {                              
      if (!handleFileRead(server.uri()))                  
        server.send(404, "text/plain", "404: Not Found"); 
    });
    server.on("/q", API_query); 
    startWifi();
  }
}

void loop(void) {
  if (wifiConnected) {
    listenWifi();
  } else {
    delay(5000);
    Serial.println("Wifi Connection failed, reset to try again");
  }
}
