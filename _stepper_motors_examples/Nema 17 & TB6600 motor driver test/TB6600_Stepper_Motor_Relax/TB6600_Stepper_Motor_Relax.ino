/*!
 * @file  DRI0043.ino
 * @brief TB6600 arduino Stepper Motor Driver is an easy-to-use professional stepper motor driver, which could control a two-phase stepping motor.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  DFRobot
 * @version  V1.0
 * @date  2023-08-03
 */


int PUL=2; //define Pulse pin
int DIR=3; //define Direction pin
int ENA=4; //define Enable Pin

int wait = 3000;

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}

void loop() {
  for (int i=0; i<200; i++)    
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(wait);
    digitalWrite(PUL,LOW);
    delayMicroseconds(wait);
  }
  for (int i=0; i<200; i++)   
  {
    digitalWrite(DIR,HIGH);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(wait);
    digitalWrite(PUL,LOW);
    delayMicroseconds(wait);
  }
  digitalWrite(ENA,LOW);
  delay(2000);
}