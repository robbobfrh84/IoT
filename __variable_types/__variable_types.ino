#include <ArduinoJson.h>

int count = 0;
bool doPrint = true;
String message = "Hello World!";

class MyClass {       
  public:             
    String name; 
    int age;        
};
MyClass data;

DynamicJsonDocument doc(512); 

void setup() {
  Serial.begin(115200);
  data.name = "Bob";
  data.age = 36;
  doc["name"] = "Tom";
  doc["age"] = 32;
}

void loop() {
  if (doPrint) {
    Serial.println("count: " + String(count));
    Serial.println("onOff: " + String(doPrint));
    Serial.println("message: " + message);
    Serial.println("data.name: " + data.name);
    Serial.println("data.age: " + String(data.age));

    int x = doc["age"];
    doc["age"] = x + 1;
    String buf;
    serializeJson(doc, buf);
    Serial.println("DynamicJson: "+buf);
    
    delay(5000);                     
    count++;
    //doPrint = !doPrint; // note OUT this line to allow for printing loop
  }
  
}
