void bluePixelWondersThroughHell(int aTime){
  Serial.println("Playing: bluePixelWondersThroughHell");

  int r = 0; int g = 0; int b = 0; int p = 28;
  int soleDelay = 1;
  int topBorder[] = {0,1,2,3,4,5,6,7};
  int rightBorder[] = {7,17,23,31,39,47,55,63};
  int bottomBorder[] = {56,57,58,59,60,61,62,63};
  int leftBorder[] = {0,8,16,24,32,40,48,56};
  int hell[64];

  long int playFor = millis();
  while(millis() - playFor < aTime){

    for (int i = 0; i < NUMPIXELS; i++){
      hell[i] += random(0,5);
      hell[i] -= random(0,5);
      if (hell[i] > 100){ hell[i] = 90; hell[i] -= random(0,10); }
      if (hell[i] < 5){ hell[i] = 5; hell[i] += random(0,10); }
      if (p != i) {pixels.setPixelColor(i, pixels.Color(hell[i],g,b)); }
    }

    if (soleDelay <=0 ){
      int m = random(1,5);
      if (valIn(topBorder, p, sizeof(topBorder)/sizeof(int))){ while (m == 4){ m = random(0,5);}}
      if (valIn(rightBorder, p, sizeof(rightBorder)/sizeof(int))){ while (m == 1){ m = random(0,5);}}
      if (valIn(bottomBorder, p, sizeof(bottomBorder)/sizeof(int))){ while (m == 3){ m = random(0,5);}}
      if (valIn(leftBorder, p, sizeof(leftBorder)/sizeof(int))){ while (m == 2){ m = random(0,5);}}
      int preP = p;
      if (m==0){p=p;} if (m==1){p+=1;} if (m==2){p-=1;} if (m==3){p+=8;} if (m==4){p-=8;}
      pixels.setPixelColor(p, pixels.Color(r,g,90));
      soleDelay = random(100,400);
    }

    delay(30); 
    soleDelay-=30;
    pixels.show();
  }

}
