const int snesPins[3] = {8,9,10}; // * Latch,Clock,Data (yellow,blue,red) | 5v (white wire) | Ground = (brown/black wire)
static bool snes[13] = {}; // * SNES Buttons Indexes as { anyPressed, B, Y, Se, St, U, D, L, R, A, X, Lt, Rt }

void setup() {
  Serial.begin(115200);
  setupSnes();
} 

void loop(){
  doSnesButtons();
}  

void doSnesButtons() {
  getSnesButtons();
  if (snes[0] == true) { // 
    Serial.print("\nButtons Pressed "); 
  }
  if (snes[1]) { Serial.print("B "); }
  if (snes[2]) { Serial.print("Y "); }
  if (snes[3]) { Serial.print("Select "); }
  if (snes[4]) { Serial.print("Start "); }
  if (snes[5]) { Serial.print("Up "); }
  if (snes[6]) { Serial.print("Down "); }
  if (snes[7]) { Serial.print("Left "); }
  if (snes[8]) { Serial.print("Right "); }
  if (snes[9]) { Serial.print("A "); }
  if (snes[10]) { Serial.print("X "); }
  if (snes[11]) { Serial.print("Top-Left "); }
  if (snes[12]) { Serial.print("Top-Right "); }
}
