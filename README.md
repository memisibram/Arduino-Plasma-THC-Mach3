# Arduino_Plasma_THC_Mach3
Mach3 plasma torch height control with Arduino

### New sketch for ESP32
I've updated the Mach3 plasma torch height control codes to work with ESP32.
They've been added to the repository as a new directory called For ESP32.

Note: These updated sketches for the ESP32 are compiled by the IDE, but since I've used the ESP32 boards I have in other projects, I haven't had a chance to try them on a real board.
The first thing I'll do when I get new boards will be to try this. I'd be grateful if you could try it and let me know the results. Thank you.

### About the project
This project was first shared by Phạm Duy Anh in 2016, and some corrections and updates were made by me in 2020.
Finally, in 2023, features to control the stepper motor driver were added to the project and it took its current form.

 - First version released by Phạm Duy Anh: https://github.com/PhamDuyAnh/Arduino_Plasma_THC
 - Video: https://www.youtube.com/watch?v=HrosZz9J61k

 - Updated by me: https://github.com/memisibram/Arduino-Plasma-THC-Mach3
 - Video: https://www.youtube.com/watch?v=IpVODe6NoKA

### Required components:
 - Arduino Nano or Uno: https://aliexpress.com/item/1005006344667667.html
 - 5V 4-Channel Relay Module: https://aliexpress.com/item/1005006064709310.html
 - Rotary Encoder & Push Button 5Pin: https://aliexpress.com/item/1005001877184897.html
 - 10K Ohm Potentiometer 3pin: https://aliexpress.com/item/1005006213044445.html
 - LCD1602+I2C 16x2 Character Display Module: https://aliexpress.com/item/32438126326.html
 - Any on off switch (optional)
 - External 5v power supply for relay module.
 - Power supply for Arduino.

### Library
  - Used library
    * <hd44780.h>

### Schematic & Connection pictures
  - USB or other all controller
![USB or other all controller](https://github.com/memisibram/Arduino-Plasma-THC-Mach3/blob/main/THC%20rotary%20Mach3%20-%20USB%20or%20other%20all%20controller/Sketch_bb.png)

  - LPT or Ethernet controller
![LPT or Ethernet controller](https://github.com/memisibram/Arduino-Plasma-THC-Mach3/blob/main/THC_rotary%20Mach3%20-%20LPT%20or%20Ethernet%20controller/Sketch_ab.png)

### License GNU GPL v3.0

### Donation

You can donate to either of us

  -  Paypal: phamduyanh@gmail.com or https://www.paypal.me/phamduyanh
  -  Paypal: memisibram@gmail.com or https://www.paypal.me/memisibram
