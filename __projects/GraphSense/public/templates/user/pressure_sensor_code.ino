/****************************************
Example Pressure Sketch for the
Adafruit Pressure Sensor
****************************************/
#include <WiFi101.h>

static char ssid[] = "YOUR WIFI SSID";
static char password[] = "YOUR WIFI PASSWORD";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
const char server[] = "pubsub.pubnub.com";
WiFiClient client;

int pressure = A0;
int delayTime = 5000;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
   Serial.begin(115200);
   delay(10);
   pinMode(pressure, INPUT);

   while (status != WL_CONNECTED) {
    Serial.print("Attempting to conenct to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    delay(10000);
   }
   printWifiStatus();
}


void loop() {
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
   int pressure = volts * 100;

   Serial.println(pressure);

    String pressureToPubnub = String(pressure);
    client.stop();
     if(client.connect(server, 80)) {
      client.println("GET /publish/pub-c-a3ff103c-13da-40f7-9134-45670c77ae43/sub-c-8740379a-1fcd-11e6-8b91-02ee2ddab7fe/0/test/0/%7B%22pressure%22%3A"+pressureToPubnub+"%7D HTTP/1.1");
      client.println("Host: pubsub.pubnub.com");
      client.println("User-Agent: ArduinoWiFi/1.1");
      client.println("Connection: close");
      client.println();
     } else {
      Serial.println("Connection failed!");
     }
   delay(500);
}

  void printWifiStatus(){
    Serial.print("SSID: ");
    Serial.print(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }
