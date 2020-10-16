#include <ArduinoJson.h>
DynamicJsonDocument json(512);
DynamicJsonDocument bodyJson(512);
#include "server/index.h"

void setupAPI() {
  json["title"] = "ESP8266 HTML and API server";
  json["pin12"] = digitalRead(button);
  json["home_page"] = "http://" + ipAddress + "/"; 
  json["api"] = "http://" + ipAddress + "/api"; 
  json["api_checkBtnState"] = "http://" + ipAddress + "/api/checkBtnState"; 
  json["example_api_query"] = "http://" + ipAddress + "/api/query?c1=red&c2=gold&num=49";
};

void setupRoutes() {
  server.on("/", Root);     // Sends index.h for client-side webapp
  server.on("/api", API);   // returns full .json api
  server.on("/api/checkBtnState", API_checkBtnState);  // Checks button state
  server.on("/api/ledToggle", HTTP_POST, API_ledToggle); // updates client requested data changes & returns current states. 
  server.on("/api/query", API_query); // takes command by query string values
};

void Root() {
  Serial.println("/");
  server.send(200, "text/html", HTML);
};

void API() {
  setCrossOrigin();
  Serial.print("/api");
  buf(json);
};

void API_ledToggle() {
  setCrossOrigin();
  String bodyString = server.arg("plain");
  deserializeJson(bodyJson, bodyString);
  Serial.println("/api/ledToggle "+bodyString);
  if (bodyJson["led"] == true){digitalWrite(led, HIGH);}else{digitalWrite(led, LOW);};
  DynamicJsonDocument data(512); 
  data["pin12"] = digitalRead(button); 
  buf(data);
};

void API_checkBtnState() {
  setCrossOrigin();
  DynamicJsonDocument data(512); 
  const bool state = digitalRead(button);
  data["pin12"] = state; 
  Serial.println("/api/checkState "+String(state));
  buf(data);
};

void API_query() {
  setCrossOrigin();
  DynamicJsonDocument data(512); 
  data["message"] = "Returning your query";
  Serial.println("/api/query");
  for (int i = 0; i < server.args(); i++) {
    Serial.println(" - "+server.argName(i)+": "+server.arg(i));
    data[server.argName(i)] = server.arg(i);
  }; 
  buf(data);
};

void buf(DynamicJsonDocument obj) {
  String buf;
  serializeJson(obj, buf);
  server.send(200, "application/json", buf);
};
