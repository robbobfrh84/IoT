void API_query() {
  setCrossOrigin();
  DynamicJsonDocument data(512); 
  data["message"] = "Returning your query";
  Serial.println("\n/?");

  for (int i = 0; i < server.args(); i++) {
    Serial.println("-"+server.argName(i)+"="+server.arg(i));
    String line = server.arg(i);
    int split = line.indexOf(",");
    
    if (server.argName(i) == "W") {
      String key = line.substring(0, split);
      String value = line.substring(split+1, line.length() );
      digitalWrite(key.toInt(), !value.toInt()); // 👀 BUILT IN ADAFRUIT HUZZAH ESP8266 are inverted for whatever reason? 
    }
    if (server.argName(i) == "R") {
      int key = server.arg(i).toInt();
      data[server.arg(i)] = digitalRead(key);
    }
    
    data[server.argName(i)] = server.arg(i);
  }; 

  buf(data);
}




