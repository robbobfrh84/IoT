bool wifiConnected = false; 
#include "server/routes.h"; // NOTE: server/wifi.h is included in server/routes.h

void setup(void) {
  Serial.begin(115200);
  pinMode(12, INPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, true);
  digitalWrite(2, true);
  setupWifi();
  if (wifiConnected) { // 🔥 Shouldn't this just be in wifi? 
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
