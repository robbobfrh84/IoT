#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>  

#include "arduino_secrets.h"
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

void setupWifi() {
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');
  wifiMulti.addAP(SECRET_SSID, SECRET_PASS);   
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { 
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           

  if (MDNS.begin("esp8266")) {              
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
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
