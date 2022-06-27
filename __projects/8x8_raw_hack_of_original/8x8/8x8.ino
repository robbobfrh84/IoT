#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6
#define NUMPIXELS      64
#include <SPI.h>
#include <WiFi101.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
WiFiClient client;

static char ssid[] = "dummy";  
static char pass[] = "dummy";

int keyIndex = 0;
int status = WL_IDLE_STATUS;
const char server[] = "pubsub.pubnub.com";    // name address for openweathermap (using DNS)

String oldAyte = "initial";
String displayedAyte = "unsigned";
String oldGal = "initial";
String galAyte;
String text;
String timeStamp = "0";
long int missedUpdateCheck;

long int noAction;

int endResponse = 0;
int cnt = 0;
int stage = 0;
boolean led6State = true;
boolean checking = false;
boolean startJson = false;
boolean recentAction = true;
boolean blank = true;
boolean refresh = false;


//web rgb *0.4, rounded down...
const char r[]={  15,200, 20, 85,  0,   40, 70, 40,130, 100,  10, 40,100, 25, 95,  0 };
const char g[]={  15,200, 40, 75, 70,   40, 20, 20, 0,  40,   70, 25, 70, 25, 120, 0 };
const char b[]={  15,200,100, 11,  0,   40, 15, 70, 0,  0,    70, 15, 80, 40, 25,  0 };

void setup(){
  Serial.begin(115200);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  pinMode(6, OUTPUT);
  pixels.begin();
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting connect to SSID..."); 
    Serial.println(ssid); 
    status = WiFi.begin(ssid, pass);
    delay(10000);
    Serial.println(ssid); 
    Serial.print("...End Attempting connect to SSID..."); 
    break;
  }

//-------------INTRO--------------INTRO-------------INTRO-------------INTRO-------------INTRO-------------//
//  printWifiStatus();
//  httpRequest("history"); //TURN BACK INTO ONE!!!
//  rainbowWormHole(5000);
  rainbowWipe(20);
//  missedUpdateCheck = millis();
//  noAction = millis();
}

//----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------//
//----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------//
//----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------VOID LOOP----------//
void loop (){

//  livePixelChat(5, 30); // check for five sec... if action will bump up to second argument...
//  if(!blank){ rainbowWipe(20); blank = true; }
//
//  lastGalCheck(10); //argument for seconds delay only if true...
//  if(!blank){ rainbowWipe(20); blank = true; }


  if (stage == 0){ Serial.println("Animation 1");
     rainbowWormHole(60000);
     rainbowWipe(20);
     stage = 1;
     delay(1000);
  }

  if (stage == 1){ Serial.println("Animation 2");
     solid(0,0,0);
     long int galDelay = millis();
     while(millis() - galDelay < 60000){
       randomPixelDanceHalfCourt(200);
     }
     rainbowWipe(20);
     stage = 2;
     delay(1000);

  }


  if (stage == 2){ Serial.println("Animation 3");
     bluePixelWondersThroughHell(60000);
     rainbowWipe(20);
     stage = 0;
     delay(1000);
  }



//  if (millis() - noAction > 1000){ Serial.println("No Action for 5 min++.");
//     solid(0,0,0);
//     long int galDelay = millis();
//     while(millis() - galDelay < 1000){
//       ;
//     }
//     //stage = 2;
//     stage = 0;
//     long int galDelay = millis();
//  }

}

//---------------------------------------------------------------------------------------------------------//
//----------         New Images and Live Update Handling                                         ----------//
//---------------------------------------------------------------------------------------------------------//

void livePixelChat(int seconds, int timeBump){ Serial.print("Seconds of ayte stream: "); Serial.println(seconds);
  displayedAyte == "" ? displayedAyte = oldAyte : displayedAyte;
  displayedAyte == "unsigned" ? displayedAyte = "": displayedAyte;
  long int playFor = millis();
  while(millis() - playFor < seconds*1000){
    if (!checking) {
      if (oldAyte != displayedAyte){ Serial.println("---!!!  NEW LIVE AYTE   !!!---");
        Serial.print("oldAyte:       "); Serial.println(oldAyte);
        Serial.print("displayedAyte: "); Serial.println(displayedAyte);
        if(oldAyte != "initial"){seconds = timeBump; Serial.print("Seconds of ayte stream: "); Serial.println(seconds); }
        recentAction = true; blank = false;
        playFor = millis();
        stage = 0;
      }
      digitalWrite(6, led6State); led6State = true ? !led6State : false;
      httpRequest("0"); delay(50);
      if (timeStamp == ""){ Serial.println("____no TimeStamp___");
        httpRequest("0"); delay(50);
      }
      httpRequest(timeStamp); delay(50);
      oldAyte = displayedAyte;
      displayedAyte = "";
    }

    parseAyte("live");

    if (millis() - missedUpdateCheck > 1000) { //Serial.println("Live History Check");
      httpRequest("history"); delay(50);
      missedUpdateCheck = millis();
    }
  }

}

void lastGalCheck(int seconds){ Serial.println("New Gallery Post Check");
  httpRequest("gal");
  recentAction = true;
  long int galDelay = millis();
  while(millis() - galDelay < 500){ //50 didn't work...check with cnt count.
    parseAyte("gal");
  }
  if (oldGal != galAyte || refresh ){ Serial.println("{{{!!! New Gallery Post !!!}}}");
    Serial.print("galAyte:       "); Serial.println(galAyte);
    Serial.print("oldGal:        "); Serial.println(oldGal);
    if (stage == 1){
      rainbowWormHole(3000); rainbowWipe(20);
      stage = 0; refresh = true;
      oldGal = galAyte; galAyte = "";
      lastGalCheck(30);
      refresh = false; return;
    } else {
      pixels.show();
      blank = false;
      stage = 0;
      delay(seconds*1000);
    }
  }
  oldGal = galAyte; galAyte = "";
}

//---------------------------------------------------------------------------------------------------------//
//----------          PubNub Reqeusts Parsing & Wifi Messages                                    ----------//
//---------------------------------------------------------------------------------------------------------//

void parseAyte(String ayte){ char c = 0;
  if (client.available()) {
    c = client.read();
    if (c == '{') { startJson = true; }
    if (startJson == true) {
      text += c;
      int x = c-65; //65-to-90 is the upperCase Alphabit ASCII
      if (c+0 >= 64 && c+0 <= 90){
        if(ayte == "live"){ displayedAyte += c; }
        if(ayte == "gal"){ galAyte += c; }
        if (recentAction){ pixels.setPixelColor(cnt, pixels.Color(r[x],g[x],b[x])); }
        cnt+=1;
        if (cnt >= 64){
          client.flush();
          if (recentAction){
            if (ayte != "gal") { pixels.show(); }
            recentAction = false;
          }
          text = ""; startJson = false; checking = false; cnt=0;
        }
      }
    }
  }
}

void httpRequest(String timeState) { // this method makes a HTTP connection to the server:
  checking = true;
  client.stop();
  if (client.connect(server, 80)) {
    if(timeState == "gal"){ //Serial.println("gallery request");
      client.println("GET /history/sub-c-f0907bae-1ab6-11e6-9f24-02ee2ddab7fe/mainGal1/0/1 HTTP/1.1"); }
    else if (timeState == "history"){ //Serial.println("Live History request");
      client.println("GET /history/sub-c-b3fbc6fa-0bf5-11e6-a8fd-02ee2ddab7fe/1b/0/1 HTTP/1.1"); }
    else { //Serial.println("else 0 or timeStamp request");
      client.println("GET /subscribe/sub-c-b3fbc6fa-0bf5-11e6-a8fd-02ee2ddab7fe/1b/0/" + timeState + " HTTP/1.1"); }
    client.println("Host: pubsub.pubnub.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }
  if(timeState == "0"){
    char c = 0;
    timeStamp = "";
    delay(50);
    for (int j = 0; j < 1000; j++){//this isn't tieing up because you put a break in....
      c = client.read();
      if (c == '['){
        for (int i = 0; i < 4; i++){ c = client.read(); }
        for (int i = 0; i < 17; i++){
          c = client.read();
          timeStamp += c;
          if (c == ']'){ break;}
        }
      }
    }
    missedUpdateCheck = millis();
    checking = false;
  }
}

void printWifiStatus() { Serial.print("SSID: ");Serial.println(WiFi.SSID());IPAddress ip = WiFi.localIP();
Serial.print("IP Address: "); Serial.println(ip);long rssi = WiFi.RSSI();
Serial.print("signal strength (RSSI):");Serial.print(rssi); Serial.println(" dBm");}

//---------------------------------------------------------------------------------------------------------//
//----------          ANIMATIONS                                                                 ----------//
//---------------------------------------------------------------------------------------------------------//

void solid(int r, int g, int b){
  for (int i = 0; i < 64; i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b));
  }
  pixels.show();
}

void rainbowWipe(int d){ Serial.println("Playing RainbowWipe...");
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
      delay(d);
  }
}

void randomPixelDanceHalfCourt(int d){ //Serial.println("Playing: Random Pixel Dance Half Court");
  for (int i = 0; i < 3; i++){
    int x = random(0,63);
    int r = random(0,90);
    int g = random(0,90);
    int b = random(0,90);
    pixels.setPixelColor(x, pixels.Color(r,g,b)); pixels.show();
    x = random(0,63); pixels.setPixelColor(x, pixels.Color(0,0,0)); pixels.show();
  }
  delay(d);
}

void rainbowWormHole(int aTime){
  Serial.println("Playing: Rainbow Wormhole");
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
  while(millis() - playFor < aTime){

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
boolean valIn(int arr[], int x, int rng){
  for (int i = 0; i < rng; i++){if (arr[i] == x){return true;}}return false;}




void bluePixelWondersThroughHell(int aTime){
  Serial.println("Playing: Blue Soul Wonders Through Hell");

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

    delay(20); soleDelay-=20;
    pixels.show();
  }

}
