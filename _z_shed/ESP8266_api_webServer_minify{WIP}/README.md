### To Do / Where I'm at...

- Maybe try platformIO?: https://platformio.org/platformio-ide
  - on a thread sombody said it was faster to compile too.
  - Instillatoin guide: https://maker.pro/arduino/tutorial/how-to-use-platformio-in-visual-studio-code-to-program-arduino

# Serving a Boilerplate HTML & API Server for ESP8266 Compatable Boards

Note: This scetch is prioritized for the *Adafruit Feather HUZZAH ESP8266* Board
- However, it's my goal to make all NodeMCU boards compatible... because they're SUPER CHEAP!

### Minify Client folder into single index.h string
- Make sure you're `cd`'ed into this directory and run...
- $`bash minify.sh`

### File structure

Arduino compiled Files
- `serve_html_api_ada.ino`: root file to execute
- `main.ino`: Vars, routes and Api hander
- Folder: `/server`: (NOTE: the arduino IDE won't show these files)
  - `wifi.h`: the files handle all the wifi settings and setups. 
  - `index.h`: This is the compiled index.html. See *Minify* instructions below.
- NOTE: other files arn't included in arduino scketch. 

While the file total and workflow maybe a bit extensive here. It's really meant to be a solid jumping off point for html/api projects going forward, in addition to a way we can have multiple boards communicating with eachother on a shared network, like a Smart Farm!

### Development Work Flow

I realized, if you're editing open files on arduino and vscode. There is cross-over issues. However, if you embed the files you want to work on within a folder and included them at the top-level .ino file, you can edit them in vs code without issue. Just have to run the sketch @ the arduino IDE.

### Resources

The Wifi esp8266 module has pretty good docs
- https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html
