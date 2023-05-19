### Where I left off
- 🟡 Adding Access Point Fallback Wifi Config to `_Template_ESP8266_ESP8266_webApp` 

### To Do 🔥
- ✅ cleanup repo docs / reorg 
- ✅ Create `ESP8266_accesPoint`
- ✅ Update `ESP8266_server` to include iphone hotspot guide.
- ✅ Create `ESP8266_wifiScan` simple copy paste from example. just add a default readme.
- 🟡 Move notes from fallback example - remove folder - push changes!
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
- [ ] No wifi found?, fallback to Access Point too add wifi info to memory
  - You'll first need to figure out how to add stuff to memory manually. 
  - Update in > `_Template_ESP8266_webApp`
- [ ] http "Open" connection between client / server ? Would remove the 1 sec callback... 
  - Update in > `_Template_ESP8266_webApp`
- [ ] Connect to Iphone hotspot ? 
  - New example? Or, just add to `_Template_ESP8266_webApp`
- [ ] New Example for Multi wifi with automatic "strongest" connection ?
  - I *don't* wanna add this to the template because it kinda gives up control. 

### Down the Road examples...
