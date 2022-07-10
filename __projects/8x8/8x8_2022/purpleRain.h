void purpleRain(int showTime) {
  Serial.println("Playing: purpleRain");

  int dropsTot = 8;
  int drops[dropsTot][5]; // [drop][ x, y, cols & length, speed, last move time ]

  int speedsTot = 5;
  int speeds[speedsTot] = { 600, 400, 300, 100, 50 }; // delay between moves
  
  int colsTot = 3;
  int cols[colsTot][5][3] = {
    {
      { 100, 15,  255 },
      { 50,  10,  100 },
      { 10,  3,   30 },
    }, {
      { 100, 15,  255 },
      { 60,  10,  100 },
      { 50,  8,   60 },
      { 10,  3,   30 },
    }, {
      { 100, 15,  255 },
      { 70,  12,  150 },
      { 30,  8,   90 },
      { 20,  5,   40 },
      { 10,  3,   30 },
    }
  };

  /* SAVE * static drops for testing */
//  drops[0][0] = { 1 };
//  drops[0][1] = { 4 };
//  drops[0][2] = { 0 };
//
//  drops[1][0] = { 3 };
//  drops[1][1] = { 5 };
//  drops[1][2] = { 1 };
//
//  drops[2][0] = { 5 };
//  drops[2][1] = { 6 };
//  drops[2][2] = { 2 };
/* SAVE * static drops for testing */

  int aboveScreen[2][2] = { {0,8}, {-8,0} }; // this is the full 8x8 screen above the one in view. where the drops start. 
  for (int i = 0; i < dropsTot; i++) {
    drops[i][0] = { random(aboveScreen[0][0],aboveScreen[0][1]) }; // X axis 
    drops[i][1] = { random(aboveScreen[1][0],aboveScreen[1][1]) }; // Y Axis 
    drops[i][2] = { random(0, colsTot) };                          // Drop length
    drops[i][3] = { random(0, speedsTot) };                        // Drop speed
    drops[i][4] = { millis() };                                    // Drop last move
  }

  long int startTime = millis();
  while(millis() - startTime < showTime) {
    int dropLength = 3;

    for (int i = 0; i < dropsTot; i++) {
      int led = drops[i][0] + (drops[i][1] * 8);
      int len = sizeof(cols[drops[i][2]])/sizeof(cols[i][drops[i][2]]);     
       
      for (int c = 0; c < len; c++) { // * Places all the drop pixels in line, fading by set col
        pixels.setPixelColor(led - ( c * 8 ), pixels.Color( 
          cols[drops[i][2]][c][0], 
          cols[drops[i][2]][c][1], 
          cols[drops[i][2]][c][2] 
        ));
      }
      pixels.setPixelColor(led - ( len * 8 ), pixels.Color(0, 0, 0));
        
      if (millis() - drops[i][4] > speeds[drops[i][3]]) {
        drops[i][1]++;
        if (drops[i][1] >= (8 + len) ) { // Reset drop to above if  bottom as cleared
          drops[i][0] = { random(aboveScreen[0][0],aboveScreen[0][1]) };  // X axis
          drops[i][1] = { random(aboveScreen[1][0],aboveScreen[1][1]) };  // y axis
          drops[i][2] = { random(0, colsTot) };                           // Drop length
          drops[i][3] = { random(0, speedsTot) };                         // Drop speed
          drops[i][4] = { millis() };                                     // Drop last move 
        }
        drops[i][4] = { millis() };
      }
    }
    pixels.show();
    delay(50);
  }
}
