# Drivers

### SparkFun EasyDriver: 
- https://www.sparkfun.com/products/12779

# Stepper Motors

### Adafruits Nema 17 Stepper Motor 
- https://www.adafruit.com/product/324 

Stepper Motor Wiring...
- Wire Colors: Red(A), Yellow(C), Green(B), Gray(D)
- Yellow assumed to be A-, and Gray to be B-

----
# NOTES

### Notes on MicroStepping and Torque with Eazy Driver
Something worth noting here..
- The EasyDriver defaults to microstepping. I found there was "hard-wired" way to get full steps. BUT, read it dosn't make it stronger...(does it make it faster tho...?). If not, maybe sticking with microsteps is what i was. 
  - See: https://forum.arduino.cc/index.php?topic=490088.0
  - Just messing around I discovered it "seems" about as strong as it was with my old code (ALSO, a shit tone quiter!)

The dual Shaft Nema17 (The first 3 steppers you got) requre 2a... EasyDriver might be limited to 750 milliamps