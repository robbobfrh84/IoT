#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "arduino_secrets.h"

void setupWifi() {
  delay(10);
  Serial.println('\n');
  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.println("Connecting ...");
  long waitForWifi = 20000;
  long timeTrack = millis();
  while ((WiFi.status() != WL_CONNECTED) && (millis() - timeTrack < waitForWifi)) {
    indicatorBlue();
    delay(150);
    indicatorYellow();
    delay(150);
    String delayed = String(millis() - timeTrack);
    Serial.print("Waiting for Wifi ("+String(waitForWifi)); Serial.println(" ms): "+delayed);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("\nWiFi.status(): ");
    Serial.println(WiFi.status());
    indicatorRed();
    delay(5000);
  } else {
    Serial.println("Connected to "); Serial.println(WiFi.SSID());
    Serial.print("IP address:\t"); Serial.println(WiFi.localIP());
    if (MDNS.begin("esp8266")) {
      Serial.println("mDNS responder started");
      wifiConnected = true;
      indicatorGreen();
    } else {
      Serial.println("Error setting up MDNS responder!");
    }
  }
}

void startWifi() {
  SPIFFS.begin();
  server.begin();
  Serial.println("HTTP server started");
}

void listenWifi(void) {
  server.handleClient();
}

void buf(DynamicJsonDocument obj) {
  String bufs;
  serializeJson(obj, bufs);
  server.send(200, "application/json", bufs);
}

void sendText(String msg) {
  server.send(200, "text/plain", msg);
}

void setCrossOrigin(){
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".png")) return "image/png";
  return "text/plain";
}

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);
  String contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
