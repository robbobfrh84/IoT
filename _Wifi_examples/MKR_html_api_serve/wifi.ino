#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h" 
#include "index.h"

char ssid[] = SECRET_SSID;        
char pass[] = SECRET_PASS;    
int keyIndex = 0;                 
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setupWifi() {

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  server.begin();
  printWiFiStatus();
  
}

void wifiListen() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n - - - new client- - - \n");
    boolean currentLineIsBlank = true;
    String line = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        line += c;
        if (c == '\n') {
          const int split = line.indexOf(":");
          String key = line.substring(0, split);
          String value = line.substring(split+2, line.length() - 2 );
          if ( key == "led" ) {
            if ( value == "true" ) {
              digitalWrite(led, HIGH);
            } else {
              digitalWrite(led, LOW);
            }
            int buttonState = digitalRead(button);
            String api_response = "button=" + String(buttonState);
            Serial.println("\n Response Data: ");
            Serial.println(api_response);
            client.println(api_response);
            break;
          }
          line = "";
        }
        if (c == '\n' && currentLineIsBlank) {
          String s = MAIN_page;
          client.println(s);
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("- - - client disconnected - - -\n");
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  digitalWrite(led, HIGH); delay(200);
  digitalWrite(led, LOW); delay(200);
  digitalWrite(led, HIGH); delay(200);
  digitalWrite(led, LOW); 

}
