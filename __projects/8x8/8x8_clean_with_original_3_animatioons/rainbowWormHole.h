#include "toolkit.h"

void rainbowWormHole(int showTime){
  Serial.println("Playing: rainbowWormHole");
  int level1[] = {27,28,35,36};
  int level2[] = {18,19,20,21,26,29,34,37,42,43,44,45};
  int level3[] = {9,10,11,12,13,14,17,22,25,30,33,38,41,46,49,50,51,52,53,54};
  int level4[] = {0,1,2,3,4,5,6,7,8,15,16,23,24,31,32,39,40,47,48,55,56,57,58,59,60,61,62,63};
  int r = 0;
  int g = 20;
  int b = 40;
  int rg = 60;
  int rd = 1;
  int gd = 1;
  int bd = 1;
  int rgd = 1;

  long int playFor = millis();
  while(millis() - playFor < showTime){

    r+=4*rd; g+=3*gd; b+=2*bd; rg+=1*rgd;

    if(r>=80){rd=rd*-1;}
    if(g>=80){gd=gd*-1;}
    if(b>=80){bd=bd*-1;}
    if(rg>=80){rgd=rgd*-1;}

    if(r<=0){rd=rd*-1;}
    if(g<=0){gd=gd*-1; g=0;}
    if(b<=0){bd=bd*-1;}
    if(rg<=0){rgd=rgd*-1;}


    for (int i = 0; i < 64; i++){
      if (valIn(level1, i, sizeof(level1)/sizeof(int))){
        pixels.setPixelColor(i, pixels.Color(r,0,0));
      }
    }
    for (int i = 0; i < 64; i++){
      if (valIn(level2, i, sizeof(level2)/sizeof(int))){
        pixels.setPixelColor(i, pixels.Color(0,g,0));
      }
    }
    for (int i = 0; i < 64; i++){
      if (valIn(level3, i, sizeof(level3)/sizeof(int))){
        pixels.setPixelColor(i, pixels.Color(0,0,b));
      }
    }
    for (int i = 0; i < 64; i++){
      if (valIn(level4, i, sizeof(level4)/sizeof(int))){
        pixels.setPixelColor(i, pixels.Color(rg,rg,0));
      }
    }
    pixels.show();
    delay(30);
  }

}
