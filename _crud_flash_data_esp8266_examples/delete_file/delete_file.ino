#include "FS.h"
String filename = "/scripts_made_me.txt";

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  SPIFFS.remove(filename);
  File checkFile = SPIFFS.open(filename, "r");
  if (checkFile) {
    Serial.println("\nThis still exists.");
  } else {
    Serial.print("\nFile deleted: "); Serial.println(filename);
  }
}

void loop(){ delay(5000); Serial.println("* Reset to rerun sketch"); }
