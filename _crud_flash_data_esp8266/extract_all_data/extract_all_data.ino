/*
   Warning !!!!!
   - Please double check Tools > Erase Flash
   - Make SURE "Only Sketch" is selected so you don't...
   - ...erase ALL your data
*/

#include "FS.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPIFFS.begin();

  Serial.println ("\n\n...Reading All File names...\n");
  Dir dir = SPIFFS.openDir("");
  while (dir.next ()) {
    Serial.print("<!filename!>:"); Serial.println(dir.fileName ());
    File file = SPIFFS.open(dir.fileName (), "r");
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
  Serial.print("<!end!>:");
}

void loop(){ delay(5000); Serial.println("* Reset microcontroller to rerun sketch"); }
