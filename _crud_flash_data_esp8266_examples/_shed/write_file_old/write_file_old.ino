#include "FS.h"
#include <ESP8266WiFi.h>
long intSleep = 1800000;  // Sleep for 30 minutes 
unsigned long prvTime = 0; //last time we took action

int loopCount() {
  int curCnt = 0;
  File f = SPIFFS.open("/count.txt", "r");
  if (!f) {
    Serial.println("Count file open failed on read.");
  } else {
    while(f.available()) {
      //Lets read line by line from the file
      String line = f.readStringUntil('\n');
      curCnt = line.toInt();
      Serial.print("Program has run ");
      Serial.print(line);
      Serial.print(" times  ");
      break; //if left in, we'll just read the first line then break out of the while.
    } 
    f.close();
  }
  f = SPIFFS.open("/count.txt", "w"); 
  if (!f) {
    Serial.println("Count file open failed on update.");
  } else {
    f.println(curCnt + 1); 
    f.close();
    Serial.println("Adding one");
  }
  return curCnt;
}

int loopReset() {
  File f = SPIFFS.open("/count.txt", "w");
  if (!f) {
    Serial.println("Count file open failed on reset.");
  } else {
    f.println(0); 
    f.close();
  }
}

void takeAction() {
  Serial.println("We did something!");
  loopReset();
}

void setup() {
  Serial.begin(112500);
  delay(10);
  SPIFFS.begin();
    Serial.println(" ok ");
  if (loopCount() > 5) {
    takeAction();
  }
  ESP.deepSleep(20000000); //20 seconds
}


void loop() {
}
