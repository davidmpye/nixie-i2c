/*
  nixie_i2c.h - Library for David Pye's nixie i2c boards.
  Created by Dr David Pye - Sept 2015
  Licenced under the GNU GPL v3
*/
#ifndef NIXIE_I2C
#define NIXIE_I2C

#define RHDP_PIN 2
#define LHDP_PIN 8

#include "Arduino.h"
#include <Adafruit_MCP23017.h>

class Nixie_i2c
{
  public:
    Nixie_i2c(uint8_t i2c_address);
    void init();
    void displayNumber(int);
    void slotMachineDisplayNumber(int);
    void blank();
    void unblank();

    void setRhdp(bool state);
    void setLhdp(bool state);
    
  private:
    int _currentNumber;
    bool _rhdpState, _lhdpState;
    Adafruit_MCP23017 _mcp;
    uint8_t _i2c_address;
    static int _pins[10];
};

#endif
