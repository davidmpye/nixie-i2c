#IN-14 Nixie Tube I2C PCB design

##Tech Specs:
Overall dimensions:
Nixie tube centre point:
Screw fixing centres:
Screw size: M3


##Parts list:
###Top side of board:
1x IN-12 nixie tube
1x Nixie tube base (3d printable one available as STL file in this folder, with cutout for WS2812B LED)
1x WS2812B LED (optional but good!)
1x MCP23017 I2C multiplexer IC (SMD)
1x 0806 anode resistor 
3x 0604 4k7 SMD resistor arrays

##Hints

-Solder the resistor arrays in to place first (flood soldering works best)
-Solder the I2C multiplexer chips and other parts in to place
-Set the I2C address bits on the rear side of the board - bridging the middle and left pad sets the bit to 0, middle and right sets the bit to 1.  Bridging all three pins shorts VCC to GND!
-If mounting PCB to the case, it's best to use nylon bolts - reducing the risk of an electrical fault allowing the anode voltage appearing on the outside of a case!
