Last time i updated this was in my 365 Hanover. 
- first uploaded the 8x8_clean_original_3_animations 
- I also had to replace the 1st, 3rd and 8th strips. so 24 pixels, three rows. I just isolated the break points and replaced the entire row. 

Original c++ code and client side code found in the ayte repo  
- https://github.com/robbobfrh84/ayte

NOTE: since moving onto mostly just esp8266, I realized this is pretty hacky and for some reason it has to try to connect to wifi or it won't animate, but it can fail... it's weird. JUST start over with esp8266 if you wanna do anything else from here. it's too much just to get to work normal. But, should work without "really" connecting to wifi (even though it HAS to try)...