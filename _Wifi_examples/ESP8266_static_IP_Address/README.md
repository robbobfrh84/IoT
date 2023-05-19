# ESP8266 Static IP Addres
- This wifi example makes it so you can specify the address of your local IP address. Which is great for routers that wanna change that all the time.

# Getting the IP GATEWAY address
- The way I do this is connect to the network(router,iphone hotspot)
- On a mac: Got to Apple Icon > System Setting > Network
- Hit the details button under the wifi selected and find the ROUTER address
  - You may need to select TPC/IP.
- Then, you cange change the last number for a custom IP... 
  - Not very custom i know, but hey. It won't change!

# Wifi config
- Copy & rename `arduino_secrets_template.h` as `arduino_secrets.h`
- Add wifi router name and passwork to new `arduino_secrets.h` file. 

### Using iphone hotspot
You may need to change the name of the hotspot to show up...
- Settings > General > About
- Change `Name` to something else. 

Make sure that you are using the 2.4GHz hotspot and NOT the 5GHz
- On iphone mini(13)....
- Settings -> Personal Hotspot -> "Maximize compatibility" ✅(enable, aka toggled 'on')

# Resources
- https://circuits4you.com/2016/12/16/esp8266-web-server-html/
- https://randomnerdtutorials.com/esp8266-nodemcu-static-fixed-ip-address-arduino/
