#include "FS.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();
  
  Serial.println ("\n\n...Reading All File names...\n");
  Dir dir = SPIFFS.openDir("");
  while (dir.next ()) {
    Serial.println("----------");
    Serial.print("File Name: "); Serial.println(dir.fileName ());
    Serial.print("File Size: "); Serial.println(dir.fileSize ());
  }
  Serial.println("* Reset to re-run sketch");
}

void loop(){ }
