void pixDance(int showTime) { //Serial.println("Playing: Random Pixel Dance Half Court");
  Serial.println("Playing: pixDance");
  long int startTime = millis();
  while(millis() - startTime < showTime) {
    for (int i = 0; i < 3; i++){
      int x = random(0,63);
      int r = random(0,90);
      int g = random(0,90);
      int b = random(0,90);
      pixels.setPixelColor(x, pixels.Color(r,g,b)); pixels.show();
      x = random(0,63); pixels.setPixelColor(x, pixels.Color(0,0,0)); pixels.show();
    }
    delay(200);
  }
}
