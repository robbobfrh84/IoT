# Where I Left off.
-...

# To Do 🟡 ✅
- 🟡 Start by reading `arduino_secrets.csv`
- 🟡 Seperate into individual strings in array. (maybe just the JSON library here)
  - Need to turn the all three IPs into array. Loop that starts at index 2?
- Change to incorrect wifi name and log condition
- Try to log on using this wifi data, make sure it works 
- add "failed to log in" condition
- Create Access Point. 
- Serve front page with simple input(s) with [SAVE] button
  - Add "*If changed and saved, restart ESP8266"
  - Button here? or make user actually restart? 

- ... * more steps need to be thought out

- Add Significant info/Steps for Access Point fallback in readme below
- REMOVE These notes!
- PUSH CHANGES!

🔥 ---- REMOVE ABOVE LINE AND PUSH CHANGES WHEN DONE ----
# Template: ESP8266 webApp
- Client & API Server: 
- Client files uploaded to and served from flash storage
- Custom IP Address: so routers don't reconfigure address
- (TO DO🔥) AccessPoint FallBack: to change wifi settings without hard code change. 

### The Skinny...
- WARNING!!! Serial monitor MUST be closed to upload files!
- Update wifi ssid, name, and static ip in `arduino_secretsh.h`
- Arduino IDE, Click Tools > ESP8266 sketch Data Upload...
- Now, upload the sketch, your files should be served at the root url

**NOTE:** This code uses the builtin pins 0 & 2 as outputs!

----
# Setup 

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
- Next, we'll configure the wifi

### Wifi Data to config 🔥
- NOTE: The files to configure, will need to be opened/edited in vs code. 
- You may not have `arduino_secrets.h` in the server folder and need to create one using the `arduino_secrets_template.h`. Rename that file `arduino_secrets.h` and add your wifi name and password.
- Find and open `server/data.h`
- Update the **Static IP Address** to match networks 
  - See examples of different router networks in code. 
- Update the **Gateway IP address** to match networks 
- Update the **Subnet IP address** to match networks 

# Getting the IP GATEWAY address
- The way I do this is connect to the network(router,iphone hotspot)
- On a mac: Got to Apple Icon > System Setting > Network
- Hit the details button under the wifi selected and find the ROUTER address
  - You may need to select TPC/IP.
- Then, you cange change the last number for a custom IP... 
  - Not very custom i know, but hey. It won't change!

### Using iphone hotspot
You may need to change the name of the hotspot to show up...
- Settings > General > About
- Change `Name` to something else. 

Make sure that you are using the 2.4GHz hotspot and NOT the 5GHz
- On iphone mini(13)....
- Settings -> Personal Hotspot -> "Maximize compatibility" ✅(enable, aka toggled 'on')

### AccessPoint FallBack: how to configure wifi router settings
🔥
- ...✨

### Resources
This was my primary word for word guide getting this work.
- NOTE: the link above with updated esptool required. The one referenced here is out of date.
- LINK: https://shepherdingelectrons.blogspot.com/2019/04/esp8266-as-spiffs-http-server.html

Wifi Status Codes:
- https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html?highlight=WiFi.status#status
- https://github.com/dlitz/ArduinoCore-esp8266/blob/master/libraries/ESP8266WiFi/src/include/wl_definitions.h
*/


----
# Notes / More...

### Why not Using wifiMult Id / Pass ?
Most examples I looked at for this used WifiMulti. Which I didn't like because it made it really difficult to debug when using multiple wifi points. You can't see what's saved, what's priority and It could connect to something you didn't want if more than 1 was available. SO, instead I used just the regular wifi with single hardcoded id/pass.

### Working, BUT Just getting a BLANK WEBPAGE?
- You forgot to flash the `/data`