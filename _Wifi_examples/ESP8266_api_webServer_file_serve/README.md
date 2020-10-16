# ESP8266 Serving client files from flash storage & dynamic API
- Testing and working Adafruit FeatherESP8266 HUZZAH

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

### Resources
This was my primary word for word guide getting this work.
- NOTE: the link above with updated esptool required. The one referenced here is out of date.
- LINK: https://shepherdingelectrons.blogspot.com/2019/04/esp8266-as-spiffs-http-server.html