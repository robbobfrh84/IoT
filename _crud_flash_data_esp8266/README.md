# CRUD flash memory(perminent) for esp8266
This example folder will show you how to create perminent memory stored on the esp8266 and a few ways to retrieve that data. Note, this readme assume I'm not going into detail on how to setup all the additional libraries and

🚨A Big fat Warning about how easy it can be to erase the data when uploading sketches.
- In the Arduino IDE, when you select tools > Erase flash, it should always default to *Only Sketch*
- SO, to erase the data you'll have to select *All Flash Contents* which it will do whenever you run any script. 🔥So, right after running and deleting the data, toggle the default BACK to *only sketch*.
- ⭐️In addition! Always double chick that it's *only sketch* when uploading other sketches with data on board.

# Example work flow

#### /create_new_file
- When Ran, this sketch will just create a new file with the hard-coded name provide.
- To add the *data* folder files, use the Arduino IDE...
  - Select Tools > ESP8266 Sketch Data Upload
  - Note: You must create a *data* folder to upload your files. the SPIFFS library only looks for that folder name when uploading files.

### /read_file_contents
- This script should print the contents of specified `filename`.
```c++
filename = "/scripts_made_me.txt";
```


# Resources
https://makersportal.com/blog/2018/2/25/python-datalogger-reading-the-serial-output-from-arduino-to-analyze-data-using-pyserial

https://diyprojects.io/esp32-get-started-spiff-library-read-write-modify-files/#google_vignette
