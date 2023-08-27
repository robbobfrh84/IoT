### Where I left off
- 🟡 Adding Access Point Fallback Wifi Config to `_Template_ESP8266_ESP8266_webApp` 

### To Do 🔥
- ✅ cleanup repo docs / reorg 
- ✅ Create `ESP8266_accesPoint`
- ✅ Update `ESP8266_server` to include iphone hotspot guide.
- ✅ Create `ESP8266_wifiScan` simple copy paste from example. just add a default readme.
- ✅ Move notes from fallback example - remove folder - push changes!
- 🟡 Update `_Template_ESP8266_webApp`...
  - ✅ Add Static Wifi
  - 🟡 Add AccessPoint fallback
  - update readme to include fallback info / guide to use. 
- [ ] Updating Jar Lights to include Static Wifi & Access Poinit fallback.
  - First test on empty board. (MAY get some problems without wiring remember!)
  - Update both "secrets" .h files. 
  - From template, in `wifi.h` add lines 9-14 & 17-19.
  - update readme to include fallback info / guide to use. 


### Next to explore
ESP8266
- 🟡 No wifi found?, fallback to Access Point too add wifi info to memory
  - Update in > `_Template_ESP8266_webApp`

ESP8266 Wifi / Template stuff...
- [ ] http "Open" connection between client / server ? Would remove the 1 sec. callback... 
  - ? Update in > `_Template_ESP8266_webApp` ?
    - Consider this as an option because you may NOT want to drain the batt. that way. BUT, after you do this maybe you realize it isn't going to work that way,,, idk...
    - Looks like what you're looking for :) > https://randomnerdtutorials.com/esp8266-nodemcu-web-server-sent-events-sse/
- [ ] New Example for Multi wifi with automatic "strongest" connection ?
  - I *don't* wanna add this to the template because it kinda gives up control. 

### Down the Road examples...
