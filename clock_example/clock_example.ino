#include <nixie_i2c.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>

#define ANODE_PWM_PIN 13

Nixie_i2c nix0(0);
Nixie_i2c nix1(1);

Nixie_i2c nix2(2);
Nixie_i2c nix3(3);
Nixie_i2c nix4(4);
Nixie_i2c nix5(5);

//   #define SET_TIME

//Descriptor for the WS2812 LEDs in the nixie boards
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, 12, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(5, 4);

  nix0.init();
  nix1.init();
  nix2.init();
  nix3.init();
  nix4.init();
  nix5.init();

  //set the tubes to full brightness
  pinMode(ANODE_PWM_PIN, OUTPUT);
  analogWrite(ANODE_PWM_PIN, 1024);

  strip.begin();
  strip.setBrightness(100);
  strip.show();

  //Get the current time from the RTC
  setSyncProvider(RTC.get);

#ifdef SET_TIME
  tmElements_t tm;
  tm.Hour = 16;             //set the tm structure to 23h31m30s on 13Feb2009
  tm.Minute = 43;
  tm.Second = 0;
  tm.Day = 03;
  tm.Month = 04;
  tm.Year = 2016 - 1970;    //tmElements_t.Year is the offset from 1970
  RTC.write(tm);
  
#endif

  setColons(true);

}

int lastMinute = -1; //used for RGB colour updates

void loop() {
  time_t currentTime = now();
  int scratch;
  scratch = hour(currentTime) / 10;
  if (nix5.currentNumber() != scratch)  nix5.slotMachineDisplayNumber(scratch);
  scratch = hour(currentTime) % 10;
  if (nix4.currentNumber() != scratch) nix4.slotMachineDisplayNumber(scratch);

  scratch = minute(currentTime) / 10;
  if (nix3.currentNumber() != scratch) nix3.slotMachineDisplayNumber(scratch);
  scratch = minute(currentTime) % 10;
  if (nix2.currentNumber() != scratch) nix2.slotMachineDisplayNumber(scratch);


  scratch = second(currentTime) / 10;
  if (nix1.currentNumber() != scratch) {
    if (nix1.currentNumber() == 5) nix1.slotMachineDisplayNumber(scratch);
    else nix1.displayNumber(scratch);
  }

  scratch = second(currentTime) % 10;
  if (nix0.currentNumber() != scratch) nix0.displayNumber(scratch);


  if (minute(currentTime) != lastMinute) {
    //The color value is set by adding hours(*10) to minutes.
    //Highest val would occur at 23:59.  (230 + 59), so cap it at 255.
    byte magicColorVal = hour(currentTime) * 10 + ( minute(currentTime) / 6) > 255 ? 255 : hour(currentTime) * 10 + (minute(currentTime) / 6) ;

    uint32_t color = Wheel(magicColorVal);

    for (int i = 0; i < 6; ++i) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    lastMinute = minute(currentTime);
  }

  //Handle dimming - we will dim from 11pm to 6am to 50% brightness...
  if (hour(currentTime) > 22 || hour(currentTime) < 6) {
    analogWrite(ANODE_PWM_PIN, 128);
    strip.setBrightness(15);
    strip.show();
  }
  else {
    analogWrite(ANODE_PWM_PIN, 1024);
      strip.setBrightness(100);
      strip.show();
  }
}


void setColons(bool state) {
  nix4.setRhdp(state);
  nix2.setRhdp(state);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



