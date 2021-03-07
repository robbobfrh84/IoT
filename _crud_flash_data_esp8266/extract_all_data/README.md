# Extract All Data

### Warning !!!!!
- 🚨Please double check Tools > Erase Flash in the Arduino IDE
- 🚨Make SURE "Only Sketch" is selected so you don't... erase ALL your data!

Using a python script, we're going to upload and run the `extract_all_data.ino` script to print the file names, then the file contents, which the python script will catch
- So, upload the `extract_all_data.ino` script first. (🚨Make SURE "Only Sketch" is selected so you don't... erase ALL your data!)
- Then, from this directory run `python extract.py` in terminal.
- Then, press the reset button on the microcontroller to log and catch all the data
- The data will be saved in the `/downloaded_data` folder in this directory :-) 🍻
