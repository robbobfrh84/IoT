#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;  
ESP8266WebServer server(80);    

String ipAddress; 
#include "server/routes.h"; // NOTE: server/wifi.h is included in server/routes.h

void setup(void) {
  Serial.begin(115200);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  setupWifi();
  server.onNotFound([]() {                              
    if (!handleFileRead(server.uri()))                  
      server.send(404, "text/plain", "404: Not Found"); 
  });
  server.on("/q", API_query); 
  startWifi();
}

void loop(void) {
  listenWifi();
  //delay(1000);
  // BOB the response is file by file, with that delay un-noted, it'll slow down the response. So, checking the sequence on the jar_light is likely slowed by client requests.
} 
