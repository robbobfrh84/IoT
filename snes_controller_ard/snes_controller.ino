int LatchPin  = snesPins[0]; // SNES Latch (yellow)
int ClockPin  = snesPins[1]; // SNES Clock (blue)
int DataPin   = snesPins[2]; // SNES Serial Data (Red)

void setupSnes() {
  pinMode(LatchPin,OUTPUT);
  pinMode(ClockPin,OUTPUT);
  pinMode(DataPin,INPUT);
  digitalWrite(LatchPin, HIGH);
  digitalWrite(ClockPin, HIGH);
}

String getSnesButton() {
  ControllerData = 0;
  digitalWrite(LatchPin, LOW);
  digitalWrite(ClockPin, HIGH);
  
  //controller needs to latch the state of all buttons
  digitalWrite(LatchPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(LatchPin,LOW);
  delayMicroseconds(6);
  
  ControllerData = digitalRead(DataPin);
  for (int i = 0; i < 16; i ++) {
    digitalWrite(ClockPin,LOW);
    delayMicroseconds(6);
    ControllerData = ControllerData << 1;
    ControllerData = ControllerData + digitalRead(DataPin);
    delayMicroseconds(6);
    digitalWrite(ClockPin,HIGH);
  }
  unsigned int ControllerDataShort = ~ControllerData;
  //String btn = getButton(ControllerDataShort);
  return getButton(ControllerDataShort);
  delay(10);
}


String getButton(unsigned int code) {
  if (code == 512) { return "LD"; } 
  else if (code == 256) { return "RD"; } 
  else if (code == 2048) { return "UD"; } 
  else if (code == 1024) { return "DD"; } 
  else if (code == 32) { return "L"; } 
  else if (code == 16) { return "R"; }
  else if (code == 128) { return "A"; } 
  else if (code == 32768) { return "B"; }
  else if (code == 64) { return "X"; } 
  else if (code == 16384) { return "Y"; }
  else if (code == 4096) { return "start"; } 
  else if (code == 8192) { return "select"; }
  else { return ""; }
}


// Left     = 512
// Right    = 256
// Up       = 2048 
// Down     = 1024
// TopLeft  = 32
// TopRight = 16
// A        = 128
// B        = 32768
// X        = 64
// Y        = 16384
// Start    = 4096
// Select   = 8192
