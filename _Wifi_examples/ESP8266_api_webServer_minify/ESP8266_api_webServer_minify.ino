#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

String ipAddress; 
#include "server/wifi.h" 

const int led = 13; // 0 is esp8266 buildin led. 
const int button = 12;

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(led, LOW);
  Serial.begin(115200);
  setupWifi();
  setupAPI();
  setupRoutes();
  startWifi();
}

void loop(void) {
  listenWifi();
}
