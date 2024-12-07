const int led1 = LED_BUILTIN;
// const int led1 = 13;

void setup() {
  pinMode(led1, OUTPUT);
}

void loop() {
  digitalWrite(led1, HIGH);  
  delay(50);                     
  digitalWrite(led1, LOW);  
  delay(1000);                     
}