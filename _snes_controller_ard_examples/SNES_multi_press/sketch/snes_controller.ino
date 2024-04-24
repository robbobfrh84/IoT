void setupSnes() {
  pinMode(snesPins[0],OUTPUT); // Latch
  pinMode(snesPins[1],OUTPUT); // Clock
  pinMode(snesPins[2],INPUT);  // Data
  digitalWrite(snesPins[0], HIGH);
  digitalWrite(snesPins[1], HIGH);
}

bool* getSnesButtons() {
  memset(snes, 0, sizeof(snes)); // * This clears the array.
  digitalWrite(snesPins[0], LOW);
  digitalWrite(snesPins[1], HIGH);
  digitalWrite(snesPins[0], HIGH); // * delayMicroseconds(12);  // 🔥 ? Seems to work fine without, Original code had it... 🤷
  digitalWrite(snesPins[0],LOW); // * delayMicroseconds(6); // 🔥 ? 
  for (int i = 1; i < 13; i++) {
    digitalWrite(snesPins[1],LOW); // * delayMicroseconds(6); // 🔥 ? 
    const bool button = !digitalRead(snesPins[2]); // delayMicroseconds(6); // 🔥 ? 
    if (button) { 
      snes[i] = true;
      snes[0] = true;
    } 
    digitalWrite(snesPins[1], HIGH);
  }
  return snes;
}