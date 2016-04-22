# Example Arduino/ESP8266 sketch

This is an example sketch for a 6-tube Nixie Clock.

The clock is designed around the IN-14 Nixie-I2C project.

##Parts needed:

-Microcontroller (ESP8266/Arduino etc)
-I2C RTC (Cheap battery-backed DS3232)
-HV PSU (I used one from [PV Electronics](http://www.pvelectronics.co.uk/) but anything suitable for driving the tubes will work.
-6 tubes and i2c boards
-I used a transistor pair to make it possible to PWM dim the HV supply to the tubes, meaning the tube brightness can be dimmed for night-time use.

The clock displays HH MM SS, and the bottom-light colour for the tubes changes throughout the day (from green in the early morning through blues in the afternoon to red by night time)
