 // Resource: https://learn.adafruit.com/photocells/arduino-code

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        // 
void setup(void) {
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
   
  photocellReading = photocellReading;
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  Serial.println("photocell: " + String(photocellReading) + " - led: " + String(LEDbrightness));   
  analogWrite(LEDpin, LEDbrightness);
 
  delay(100);
}
