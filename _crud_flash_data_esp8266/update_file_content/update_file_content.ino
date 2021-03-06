#include "FS.h"
String filename = "/scripts_made_me.txt";

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  
  File file = SPIFFS.open(filename, "a");
  if (!file) {
    Serial.println("\nFile not found :(");
  } else {
    Serial.print("\nUpdating file: "); Serial.println(filename);
    file.println("emily,35,emily@mail.com");
  }
}

void loop(){ delay(5000); Serial.println("* Reset to rerun sketch"); }
