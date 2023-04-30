const int LatchPin  = snesPins[0]; // SNES Latch (yellow)
const int ClockPin  = snesPins[1]; // SNES Clock (blue)
const int DataPin   = snesPins[2]; // SNES Serial Data (Red)

long int buttonsDown = 0;
String buttonsString = "";
const int totalButtons = 12;
const String buttonKeys[totalButtons][2] = {
  { "512",  "L" },  // D-Left   = 512
  { "256",  "R" },  // D-Right  = 256
  { "2048", "U" },  // D-Up     = 2048 
  { "1024", "D" },  // D-Down   = 1024
  { "32",   "T"},   // TopLeft  = 32
  { "16",   "P"},   // TopRight = 16
  { "128",  "A" },  // A        = 128
  { "32768","B" },  // B        = 32768
  { "64",   "X" },  // X        = 64
  { "16384","Y" },  // Y        = 16384
  { "4096", "S"},   // Start    = 4096
  { "8192", "E"}    // Select   = 8192
};

void setupSnes() {
  pinMode(LatchPin,OUTPUT);
  pinMode(ClockPin,OUTPUT);
  pinMode(DataPin,INPUT);
  digitalWrite(LatchPin, HIGH);
  digitalWrite(ClockPin, HIGH);
}

String getSnesButton() {
  long int ControllerData = 0;
  digitalWrite(LatchPin, LOW);
  digitalWrite(ClockPin, HIGH);
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
  return getButton(ControllerDataShort);
}


String getButton(long int code) {
  const String codeString = String(code);
  for (int i = 0; i < totalButtons; i++) {
    if (codeString == buttonKeys[i][0]) {
      buttonsDown = code;
      buttonsString = buttonKeys[i][1];
      return buttonsString;
      break;
    }
  }
  if (code == buttonsDown) {
    return buttonsString;
  }
  if (code > 0) {
    return checkMulti(code);
  } else {
    buttonsString = "";
    buttonsDown = 0;
    return "";
  }
} 

String checkMulti(long int code) {
  String codeString = String(code - buttonsDown);
  for (int i = 0; i < totalButtons; i++) {
    if (codeString == buttonKeys[i][0]) {
      buttonsDown = code;
      buttonsString = buttonsString + "+" + buttonKeys[i][1];
      return buttonsString;
      break;
    }
  }
  codeString = String(buttonsDown - code);
  for (int i = 0; i < totalButtons; i++) {
    if (codeString == buttonKeys[i][0]) {
      buttonsDown = code;
      buttonsString = removeBtn( buttonKeys[i][1],  buttonsString);
      return buttonsString;
      break;
    }
  }
  buttonsString = "";
  buttonsDown = 0;
  return "";
}

String removeBtn(String btn, String buttons) {
  String clipped = "";
  for (int i=0; i < buttons.length(); i++) { 
    if ( (buttons.charAt(i) != '+') && (String(buttons.charAt(i)) != btn) ) { 
      if (clipped.length() > 0) {
        clipped += "+";
      }
      clipped += buttons.charAt(i);
    }
  }
  return clipped;
}
