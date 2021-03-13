int count = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("count: " + String(count));
  delay(1000);                     
  count++;
}
