#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "arduino_secrets.h"

void setupWifi() {
  delay(10);
  Serial.println('\n');
  wifiMulti.addAP(SECRET_SSID, SECRET_PASS);
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    indicatorYellow();
    delay(125);
    indicatorRed();
    delay(125);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
    Serial.println("mDNS responder started");
    indicatorGreen();
  } else {
    Serial.println("Error setting up MDNS responder!");
    indicatorRed();
  }
}

void startWifi() {
  SPIFFS.begin();
  server.begin();
  Serial.println("HTTP server started");
}

void listenWifi(void) {
  server.handleClient();
  if (clientPause) {
    delay(100);
    Serial.println("\n\n  clientPause: \n");
    clientPause = false;
  }
  // if (clientPause < 500) {
  //   clientPause += clientPause + 1;
  // }
  // clientPause += clientPause + 1;
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
  Serial.print("handleFileRead: " + path);
  // String count = String(clientPause);
  // Serial.println(" - clientPause: " + count);

  if (path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    clientPause = true;

    File file = SPIFFS.open(path, "r");
    // size_t sent = server.streamFile(file, contentType);
    server.streamFile(file, contentType);
    Serial.println("\nSent: " + path);
    file.close();
    // clientPause = false;
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
