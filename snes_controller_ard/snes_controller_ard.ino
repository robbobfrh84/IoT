// SNES NOTE: 5v (white wire), Ground = (brown/black wire)
const int snesPins[3] = {8,9,10}; // Latch,Clock,Data (yellow,blue,red)
String snes;

unsigned int ControllerData = 0;

void setup() {
  Serial.begin(115200);
  setupSnes();
} 

void loop(){
  snes = getSnesButton();
  if (snes != "") {
    Serial.println(snes+" Button Pressed"); 
  }
}  
