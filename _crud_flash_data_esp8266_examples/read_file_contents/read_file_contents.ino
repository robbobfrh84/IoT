#include "FS.h"
String filename = "/scripts_made_me.txt";

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  
  File file = SPIFFS.open(filename, "r");
  if (!file) {
    Serial.println("\nFile not found :(");
  } else {
    while(file.available()) {
      String line = file.readStringUntil('\n');
      Serial.println(line);
    } 
    file.close();
  }
}

void loop(){ delay(5000); Serial.println(" * Reset to rerun sketch"); }
