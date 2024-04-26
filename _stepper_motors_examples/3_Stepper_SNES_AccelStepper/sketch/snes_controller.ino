void handleFreeMove() {
  int steps = 0;
  if (snes[7]) { xGo = true; xStopped = false; stepperX.move(maxSpeed); digitalWrite(3, HIGH); } // * Left with 🐛 AccellStepper Bug Fix!
  if (snes[8]) { xGo = true; xStopped = false; stepperX.move(maxSpeed * -1); } // * (CCW) Right
  if (snes[5]) { yGo = true; yStopped = false; stepperY.move(maxSpeed); digitalWrite(3, HIGH); } // * Up with 🐛 AccellStepper Bug Fix!
  if (snes[6]) { yGo = true; yStopped = false; stepperY.move(maxSpeed * -1); } // * CCW) Down
  if (snes[11]) { zGo = true; zStopped = false; stepperZ.move(maxSpeed); digitalWrite(3, HIGH); } // * Top-Left 🐛 AccellStepper Bug Fix!
  if (snes[12]) { zGo = true; zStopped = false; stepperZ.move(maxSpeed * -1); } // * (CCW) Top-Right
}

void chunkMove(int steps, int chunkDelay) {
  bool xGoTo = false; bool yGoTo = false; bool zGoTo = false;
  if ((snes[7] || snes[8]) && xStopped) { xGoTo = true; } // * Left, Right
  if ((snes[5] || snes[6]) && yStopped) { yGoTo = true; } // * Up, Down
  if ((snes[11] || snes[12]) && zStopped) { zGoTo = true; } // * Top-Left, Top-Right
  if (snes[8] || snes[6] || snes[12]) { steps = steps * -1; } // * Right, Down, Top-Right (CCW)
  if (snes[7]) { digitalWrite(3, HIGH); } // * 🐛 AccellStepper Bug Fix!
  if (snes[5]) { digitalWrite(6, HIGH); } // * 🐛 AccellStepper Bug Fix!
  if (snes[11]) { digitalWrite(A1, HIGH); } // * 🐛 AccellStepper Bug Fix!
  if (xGoTo) {
    stepperX.runToNewPosition(stepperX.currentPosition() + steps );
    delay(chunkDelay);
  }
  if (yGoTo) {
    stepperY.runToNewPosition(stepperY.currentPosition() + steps );
    delay(chunkDelay);
  }
  if (zGoTo) {
    stepperZ.runToNewPosition(stepperZ.currentPosition() + steps );
    delay(chunkDelay);
  }
}

void speedChange() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastSpeedChangeMillis >= holdForSpeedChange) {
    lastSpeedChangeMillis = currentMillis;
    const int totalSpeeds = sizeof(speeds) / sizeof(speeds[0]);
    speedIndex++;
    if (speedIndex >= totalSpeeds) { speedIndex = 0; }
    currentSpeed = speeds[speedIndex] * maxSpeed;
    stepperX.setMaxSpeed(currentSpeed);
    stepperY.setMaxSpeed(currentSpeed);
    stepperZ.setMaxSpeed(currentSpeed);
  }
}

void handleAxes() {

  if (xGo) { stepperX.run();
  } else if (!xStopped) {
    stepperX.move(0);
    if (!stepperX.isRunning()) { xStopped = true; }
    stepperX.run();
  }

  if (yGo) { stepperY.run();
  } else if (!yStopped) {
    stepperY.move(0);
    if (!stepperY.isRunning()) { yStopped = true; }
    stepperY.run();
  }

  if (zGo) { stepperZ.run();
  } else if (!zStopped) {
    stepperZ.move(0);
    if (!stepperZ.isRunning()) { zStopped = true; }
    stepperZ.run();
  }

}

/* Handling Shift Register for SNES */
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