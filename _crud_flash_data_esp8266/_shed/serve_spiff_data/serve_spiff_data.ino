void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void handleDownload(){
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS failed to mount !\r\n");                   
  }
  else {
    String str = "";
    File f = SPIFFS.open(server.arg(0), "r");
    if (!f) {
      Serial.println("Can't open SPIFFS file !\r\n");         
    }
    else {
      char buf[1024];
      int siz = f.size();
      while(siz > 0) {
        size_t len = std::min((int)(sizeof(buf) - 1), siz);
        f.read((uint8_t *)buf, len);
        buf[len] = 0;
        str += buf;
        siz -= sizeof(buf) - 1;
      }
      f.close();
      server.send(200, "text/plain", str);
    }
  }
}
