#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ArduinoJson.h>

ESP8266WebServer server(80);
DynamicJsonDocument wifiJSON(512);

String wifiConfig = "/wifiConfig.json";
bool wifiConnected = false; 

/* 👇 ORDER MATTERS 👇 */
#include "toolkit.h";
#include "routes.h"; 
#include "wifi.h";

void do_setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  pinMode(12, INPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, true);
  digitalWrite(2, true);
  get_Wifi_Config();
  setupWifi();
  startWifi();
}

void do_loop() {
 if (wifiConnected) { 
    listenWifi();     
  } else {
    Serial.println("Wifi Connection failed, reset to try again");
  }
}

