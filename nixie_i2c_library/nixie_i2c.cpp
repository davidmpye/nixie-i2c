/*
  nixie_i2c.cpp - Library for David Pye's nixie i2c boards.
  Created by Dr David Pye - Sept 2015
  Licenced under the GNU GPL v3
*/
#include <nixie_i2c.h>

int Nixie_i2c::_pins[10] = { 3, 9, 10, 11, 12, 13, 7, 6, 5, 4 };

Nixie_i2c::Nixie_i2c(uint8_t i2c_address) {
  _i2c_address = i2c_address;
  
  _currentNumber = 0;
  _lhdpState = _rhdpState = false;
}

void Nixie_i2c::init() {
  _mcp.begin(_i2c_address);
  //Set all pins to o/p
  for (int i=0; i<16; ++i) _mcp.pinMode(i, OUTPUT);
  blank();
}

void Nixie_i2c::displayNumber(int number) {
  _currentNumber = number;
  unblank();
}

void Nixie_i2c::slotMachineDisplayNumber(int newNumber) {

  int numPasses;
  if (_currentNumber == newNumber) numPasses = 1; else numPasses = 2; //only do 1 pass

  bool orig_lhdp = _lhdpState;
  bool orig_rhdp = _rhdpState;

  int num = _currentNumber;
  int passes = 0;

  while (1) {
    if (num == 9) num = 0; else num++;

    //toggle the lhdp/rhdp cathodes as we go round.
    _lhdpState = !_lhdpState;
    _rhdpState = !_rhdpState;
  
    if (num == newNumber) {
      //reset the lhdp/rhdp states in case we stop here!
      _lhdpState = orig_lhdp;
      _rhdpState = orig_rhdp;
      passes ++;
    }
    displayNumber(num);
    if (passes == numPasses) break;
    delay(50);
  }
}

void Nixie_i2c::blank() {
  //Set all outputs low
  _mcp.writeGPIOAB(0x0000);
}

void Nixie_i2c::unblank() {
  uint16_t b = 0x0000;
  if (_rhdpState) b |= 1<<RHDP_PIN;
  if (_lhdpState) b |= 1<<LHDP_PIN;
  b |= 1 << _pins[_currentNumber];
  _mcp.writeGPIOAB(b);
}

void Nixie_i2c::setRhdp(bool state) {
  _rhdpState = state;
  _mcp.digitalWrite(RHDP_PIN, _rhdpState ? HIGH: LOW);
}

void Nixie_i2c::setLhdp(bool state) {
  _lhdpState = state;
  _mcp.digitalWrite(LHDP_PIN, _lhdpState ? HIGH: LOW);
}
    
