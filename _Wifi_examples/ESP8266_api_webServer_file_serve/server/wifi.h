#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "arduino_secrets.h"
const char* ssid = SECRET_SSID; // found in arduino_secrets.h (.gitignored!)
const char* password = SECRET_PASS; // found in arduino_secrets.h (.gitignored!)

void setupWifi() {
  Serial.begin(115200);
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
    Serial.println(WiFi.status());
    /*
      Doc Reference for status codes...
      - https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html?highlight=WiFi.status#status
      - https://github.com/dlitz/ArduinoCore-esp8266/blob/master/libraries/ESP8266WiFi/src/include/wl_definitions.h
    */
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
  return "text/plain";
}

bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";
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
