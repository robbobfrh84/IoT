# Setup 

- Code: `basic_move/basic_move.ino`
- Motor Driver: [TB6600 4A 9-42V](https://www.amazon.com/UsongShine-Stepper-Controller-Arduino-Printer/dp/B07HHS14VQ/ref=sr_1_5?dib=eyJ2IjoiMSJ9.OnxCTCbzanT87D11zrinldgp0WckCWEucTJRWSGitKHhea7YLYr1_4wqvlZ3YzbTxXhTjNbaRvYTF6NoF5Fkt36rDBG7orIIl0D1_f57kkp5Yadi6lu9ip0zkNZb6mW0I_OoaEkTV8YVE-3RWsg_NkdxxVzlHI3_hCMyjSvvlDJb95OYHAjPCiZ-LzOYhKUEdzZLUIbAod0BhotPXly0_ZtNDITjgFYgVb5TPvfKA-keBDEOT6HsbL7VlBdGTuL6E5fg2JSz94n_XoVqk57IhSUDN0LZCdeZAthqAJv01QI.gCg06C994NT-2DhQ86nCfVXbg2U_1Z8VoqGR0vCSvZ8&dib_tag=se&keywords=tb6600%2Bstepper%2Bmotor%2Bdriver&qid=1708548998&sr=8-5&th=1) Motor Driver
- Followed this video guide: https://www.youtube.com/watch?v=FggSRQqB_a4
- But, the wiring from this guide: Guide: https://wiki.dfrobot.com/TB6600_Stepper_Motor_Driver_SKU__DRI0043
- See photos for wiring and code.
- Used: **Arduino UNO**.
- Used: Adafruit's Nema 17.

### Arduino UNO Setup

- Use wiring from the TB600 docs rather than what the guy does on the video.	
  - Wiring from the video works, but not correct to enable motor "relax"

- Remainder of wiring for GND can be continued connected by stringing together from all - GNDs.
- Remainder of wiring is straight forward. 

### Motor Driver Settings

- MicroStep: 1 - ON, ON, OFF (for big steps 200/rotation)
- **MicroStep: 4 - ON, OFF, OFF** (for Medium 800/rotation)
- MicroStep: 16 - ON, ON, OFF (for Short steps: 3200/rotation)
- Set Current(A) to motor specs
- Power source: 12v 1.5 A Adapter. (White one I've used before)

### Finding The correct Motor Wires

- Use a Multimeter to check for resistance between two wires. If the reading is low. Then, that's your pair! It's confusing because I want to think if it's high! But check with your skin.
- It doesn't seem to mater what order the wires go in... They may need to be switch for direction, or, I got lucky. See photos to wire how I did. 



### Nema 17 

- [Specs Link (adafruit)](https://www.adafruit.com/product/324?gad_source=1&gclid=CjwKCAiArfauBhApEiwAeoB7qLCuDdzGzsufwnYixoJa5m-bZBLVgJRRvfmt9jZyWdNDxCzGMrDaKBoCFDUQAvD_BwE)
  - 200 steps/rev
  - 12V 
  - 350mA
- Motor Driver Setup: 
  - Microstep: See "Motor Driver Settings" above
  - Current: I set this at the lowest: 0.5 (specs says 350mA, so don't need more)
    - ON, ON, ON
- The 6 switches should be: ON, OFF, OFF, ON, ON, ON (for 4 micro steps & .5 amps)
- 🚨 Important: Match the delay settings for the Microstep settings with related `delay()` or `delayMicroseconds()`. It may not work if the delay is too short for bigger steps, like 1 (200 steps per rotation). 
- Notes: 
  - It gets really hot. Not sure if that's because it's allowed to draw max amps 350mA. But Whenever I read about it, people say they get hot. That's why the cooling fin