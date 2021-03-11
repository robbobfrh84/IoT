# Interactive Jar Lights with client server

WARNING: if you're running this sketch without the pins hooked up, it will behave very oddly. One major factor is the input pin, which will hog up the process due to the fact that it will trigger True without being hooked up, while false is the default state when it is hooked up!
- The sketch will run, but the wifi will be really buggy and slow. 

### Data to config

Wifi settings.
- SERVER: You may not have `arduino_secrets.h` in the server folder and need to create one using the `arduino_secrets_template.h` with you wifi name and password.
Update your microcontroller's designated url on your network.
- CLIENT: In the `data` folder, find the `js` folder. There, open `the index.js` and update the `const url = "http://192.168.1.140";` file to match your devices url.
- Note: you can get your url by running the Arduino script with the serial monitor open to see the url print.

### Known issues/ fixes /features.

Slow upload:
- the project uploads 10+ files. it works fine at the moment. But, going foward, it'd be better to compile all into one index.html. still need images, but one large html would speed things up as a start.

### References

See: `../_Wifi_examples/ESP8266_api_webServer_file_serve`
- Base code for serving client-side data and api.
