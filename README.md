# nixie-i2c

Nixie-I2C is a collection of PCB designs and accompanying library designed to simplify using [Nixie tubes](http://en.wikipedia.org/wiki/Nixie_tube) with Arduino and ESP8266 based boards (and perhaps others in future).

## Design

Driving nixie tubes from microcontrollers can present several issues:
 - Can rely on expensive/obsolute/irreplacable Soviet-era driver ICs (eg K155ID1)
 - Or, if you drive the cathodes directly, requires a large number of pins from the microcontroller (e.g a numeric IN-14 nixie tube has 12 cathodes - 0-9 and left/right decimal places), so it becomes difficult to direct-drive multiple tubes without running out of IO pins
 - If using the 'direct drive' solution above, you need a high-voltage capable transistor per cathode.
 
The main idea of this project is to provide a convenient driver board for a nixie tube, allowing it to be controlled from the microcontroller via I2C.

## Features

The PCB design here (which is tested and works) offers the following features:
 - Bus based (I2C) - put all your tubes in a row on stripboard or similar!
 - Designed for IN-14 nixie tube
 - I2C address (3-bit) settable (solder-pads on underside of board), allowing 9 nixie tubes per I2C bus.
 - Handles all HV switching, allowing a simple library interface to select the digit to be displayed
 - Has option for installing a programmable RGB (WS2812B) LED under the base of each tube, allowing bottom-lighting of any colour/brightness, without requiring ongoing control from the microcontroller (eg no PWM timing loops etc)
 - Eagle brd/sch files provided
 - Licenced under the OSHW framework
 
 There is an accompanying library, which supports:
 - Arduino or ESP8266
 - Simple interface to setting a tube's display digit / decimal point status
 - Slot-machine display for cathode protection
 - Direct drive for up to 9 tubes (per I2C bus), no multiplexing/timer loops from the microntroller required
 
##Example

 The library is designed to be simple and easy to use:
 ```
 Nixie_i2c nix0(0x00);
 nix0.slotMachineDisplayNumber(1);  //Tube now displays 1
 delay(1000);
 nix0.slotMachineDisplayNumber(9);  //Tube now displays 9
 ```
