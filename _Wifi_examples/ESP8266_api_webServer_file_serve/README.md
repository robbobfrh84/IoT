# ESP8266 Serving client files from flash storage & dynamic API
- Testing and working Adafruit FeatherESP8266 HUZZAH
- NOTE: this example code requires you to Add files manually to board, separate from normal upload of sketch.

### Intall esptool tool
- NOTE: what the resource link below was great. But, I was an outdated esptool that IS required. Rather use this version...
- download .zip: https://github.com/esp8266/arduino-esp8266fs-plugin/releases/tag/0.5.0
- Unzip this and put the folder in the `~/Arduino/tools` folder.
  - NOTE: you may have to create the `tools` folder.
  - Just to not be confused the full path now to the unzipped lib is `~/Arduino/tools/ESP8266FS/tool/esp8266fs.jar`
  - Don't need to know that, it's just the subfolder tool makes it confusing.
  - Once it's unzip reboot Arduino IDE...

### Add Files to board.
- WARNING!!! Serial monitor MUST be closed to upload files!
- Once you've installed the esptool and rebooted the Arduino IDE, Click Tools > ESP8266 sketch Data Upload...
- This will add all the files in the `/data` folder onto the ESP8266
- Now, upload the sketch, now your files should be served at the root url

### Data to config
Wifi settings.
- You may not have `arduino_secrets.h` in the server folder and need to create one using the `arduino_secrets_template.h` with you wifi name and password.
Update your microcontroller's designated url on your network.
- In the `data` folder, find the `js` folder. There, open `the index.js` and update the `const url = "http://192.168.1.140";` file to match your devices url.
- Note: you can get your url by running the Arduino script with the serial monitor open to see the url print.

### Why not Using wifiMult Id / Pass ?
Most examples I looked at for this used WifiMulti. Which I didn't like because it made it really difficult to debug when using multiple wifi points. You can't see what's saved, what's priority and It could connect to something you didn't want if more than 1 was available. SO, instead I used just the regular wifi with single hardcoded id/pass.

### Resources
This was my primary word for word guide getting this work.
- NOTE: the link above with updated esptool required. The one referenced here is out of date.
- LINK: https://shepherdingelectrons.blogspot.com/2019/04/esp8266-as-spiffs-http-server.html

Wifi Status Codes:
- https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html?highlight=WiFi.status#status
- https://github.com/dlitz/ArduinoCore-esp8266/blob/master/libraries/ESP8266WiFi/src/include/wl_definitions.h
*/
