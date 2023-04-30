#Update To Do List
- 🟡 Check to make sure it works as expected
  - ✅ client uses `location.origin`
  - ✅ Change name to be `_Template_ESP8266_API_Server_Flash_Client`
  - ✅ Change to use built-in leds 
  - ✅ why "DW" and "DR", change to "W" "R" ?
  - ✅ Oh check title. it says MKR!!! needs to be ESP8266
  - 🟡 Add static wifi
  - Review rest of code. 
    - `#include <ESP8266WiFi.h>` 2x of these in wifi.h


- Document: 
  - Review this guide and clean / re 
  - mention static wifi config. 
  - mention adafruit HUZZAH builtin pins 0 & 2 as outputs
  - This is messy and a lot can go in #resources / add a **THE SKINNY**
- Remove this to do list and push changes!

IF YOU'RE FEELING CRAZY. START NEW Example -> maybe figureout how to do an "Open" connection between client / server to remove the need for the 1 sec timer....

----
# Template: ESP8266 dynamic API Server & client files from flash storage

### The Skinny...
- WARNING!!! Serial monitor MUST be closed to upload files!
- Arduino IDE, Click Tools > ESP8266 sketch Data Upload...
- Now, upload the sketch, your files should be served at the root url

### Install and setup esptool tool (already done on 2018 Pro & Pi)
- NOTE: while the resource link below was great, it used an outdated esptool that IS required. Rather use this version...
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
  - NOTE: you can only edit and see the root project folder's corresponding `.ino` file. All other files need to be edited in vs code. 
- Now, your files should be served at the root url
- Next, we'll configure he wifi

### Wifi Data to config 🔥
- NOTE: The files to configure, will need to be opened/edited in vs code. 
- You may not have `arduino_secrets.h` in the server folder and need to create one using the `arduino_secrets_template.h`. Rename that file `arduino_secrets.h` and add your wifi name and password.
- Find and open `server/data.h`
- Update the **Static IP Address** to match networks 
  - See example of different router networks in code. 
- Update the **Gateway IP address** to match networks 


----
# Notes / More...

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
