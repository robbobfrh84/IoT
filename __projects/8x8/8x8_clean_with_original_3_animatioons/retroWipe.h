void retroWipe() { 
  Serial.println("Playing: retroWipe");
  for (int i = 0; i < 77; i++){
    pixels.setPixelColor(i, pixels.Color(100,100,100));
    pixels.setPixelColor(i-1, pixels.Color(64,0,0)); pixels.setPixelColor(i-2, pixels.Color(45,15,0));
    pixels.setPixelColor(i-3, pixels.Color(28,28,0)); pixels.setPixelColor(i-4, pixels.Color(14,38,0));
    pixels.setPixelColor(i-5, pixels.Color(0,48,0)); pixels.setPixelColor(i-6, pixels.Color(0,32,12));
    pixels.setPixelColor(i-7, pixels.Color(0,20,20)); pixels.setPixelColor(i-8, pixels.Color(0,9,27));
    pixels.setPixelColor(i-9, pixels.Color(0,0,32)); pixels.setPixelColor(i-10, pixels.Color(7,0,21));
    pixels.setPixelColor(i-11, pixels.Color(12,0,12)); pixels.setPixelColor(i-12, pixels.Color(15,0,5));
    pixels.setPixelColor(i-13, pixels.Color(0,0,0));
    pixels.show();
    delay(20);
  }
}
