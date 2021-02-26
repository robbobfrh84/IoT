// ESP8266 SPIFFS Basic Reading and Writing File - Resource: https://circuits4you.com/2018/01/31/example-of-esp8266-flash-file-system-spiffs/
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers

const char* filename = "/samplefile.txt";

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  if(SPIFFS.begin()) {
    Serial.println("SPIFFS Initialize....ok");
  } else {
    Serial.println("SPIFFS Initialization...failed");
  }

  if(SPIFFS.format()) {
    Serial.println("File System Formated");
  } else {
    Serial.println("File System Formatting Error");
  }

  File f = SPIFFS.open(filename, "a");
  
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("Writing Data to File");
    f.println("This is sample data which is written in file");
    f.close();  //Close file
  }

}

void loop() {
  int i;
  
  File f = SPIFFS.open(filename, "r");
  
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("Reading Data from File:");
    for(i=0; i<f.size(); i++) {
      Serial.print((char)f.read());
    }
    f.close(); 
    Serial.println("File Closed");
  }
  
  delay(5000);
}
