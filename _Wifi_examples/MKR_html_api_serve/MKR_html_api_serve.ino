const int led = 13;
const int button = 7;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(led, LOW); 
  Serial.begin(9600);
  setupWifi();
}

void loop() {
  wifiListen();  
}
