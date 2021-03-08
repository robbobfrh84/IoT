# Interactive Jar Lights with client server

### Data to config

Wifi settings.
- You may not have `arduino_secrets.h` in the server folder and need to create one using the `arduino_secrets_template.h` with you wifi name and password.
Update your microcontroller's designated url on your network.
- In the `data` folder, find the `js` folder. There, open `the index.js` and update the `const url = "http://192.168.1.140";` file to match your devices url.
- Note: you can get your url by running the Arduino script with the serial monitor open to see the url print.
