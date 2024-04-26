void mainLoop() {
  doSnesButtons();
}

void doSnesButtons() {
  xGo = false; yGo = false; zGo = false; // * Reset controller Axis motor state.
  getSnesButtons(); // * SNES Buttons Indexes as { anyPressed, B, Y, Se, St, U, D, L, R, A, X, Lt, Rt }
  if (snes[0] == true) { // * ANY Button
    if (snes[1]) { handleFreeMove(); } // * B Button
    if (snes[4]) { chunkMove(1, longChunkDelay); } // * Start Button
    if (snes[3]) { chunkMove(microSteps, longChunkDelay); } // * Select Button
    if (snes[9]) { chunkMove((revSteps * microSteps) / 4, shortChunkDelay); } // * A Button
    if (snes[10]) { chunkMove(revSteps * microSteps,  shortChunkDelay); } // * X Button
    if (snes[2]) { speedChange(); } else { lastSpeedChangeMillis = 0; } // * Y Button (Change Speeds)
  }
  handleAxes();
}