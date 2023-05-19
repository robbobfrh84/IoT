#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "arduino_secrets.h" 

const char* ssid = SECRET_SSID; // found in arduino_secrets.h (.gitignored!). But should have arduino_secrets_template.h 
const char* password = SECRET_PASS;// found in arduino_secrets.h (.gitignored!). But should have arduino_secrets_template.h 
IPAddress local_IP(IP_A[0], IP_A[1], IP_A[2], IP_A[3]); 
IPAddress gateway(IP_G[0], IP_G[1], IP_G[2], IP_G[3]); 
IPAddress subnet(IP_S[0], IP_S[1], IP_S[2], IP_S[3]);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

ESP8266WebServer server(80);

const int led = 2;

void handleRoot() {
  digitalWrite(led, true);
  const String ip = WiFi.localIP().toString();
  const String html = "<h1>IP Address: "+ip+"</h1>";
  server.send(200, "text/html", html);
  delay(500);
  digitalWrite(led, false);
}

void handleNotFound() {
  digitalWrite(led, true);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, false);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, false);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
