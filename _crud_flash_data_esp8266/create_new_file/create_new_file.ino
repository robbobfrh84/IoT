#include "FS.h"
String filename = "/scripts_made_me.txt";

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  
  File checkFile = SPIFFS.open(filename, "r");
  if (checkFile) {
    Serial.println("\nThis file already exists.");
  } else {
    Serial.print("\nCreating new file: "); Serial.println(filename);
    File file = SPIFFS.open(filename, "w");
    file.print("name,number,email\n");
    file.print("bob,49,bob@mail.com\n");
  }
}

void loop(){ delay(5000); Serial.println("* Reset to rerun sketch"); }
