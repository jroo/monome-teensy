/*
  Monome.h - Library for communicating with Monome devices over USB via monome serial protocol.
  Created by Josh Ruihley, January 25, 2022.
*/
#ifndef MONOME_H
#define MONOME_H

#if ARDUINO
#include "Arduino.h"
#else
#include <inttypes.h>
typedef uint8_t byte;
#endif

#if defined(ARDUINO_TEENSY36) || defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#include "USBHost_t36.h"
#else
#error *** Monome-teensy only works with Teensy 3.6 or Teensy 4.x. Please select it in Tools > Boards ***
#endif

struct coords {
  byte x;
  byte y;
};

class Monome 
{
  public:
    Monome();
    void setup();
    void loop();
    void setOverallInt(byte i);
    void setLed(byte x, byte y, byte s);
    void setLedInt(byte x, byte y, byte i);
    void setAll(byte s);
    void setAllInt(byte i);    
    void setRow(byte x, byte y, byte d);
    void setLevelRow(byte x, byte y, byte d[8]);
    void setCol(byte x, byte y, byte d);
    void setLevelCol(byte x, byte y, byte d[8]);
    void setMap(byte x, byte y, byte d[8]);
    void setLevelMap(byte x, byte y, byte d[32]);
    byte keyPressed[256];
    byte coordsToKey(coords c);
    coords keyToCoords(byte k);

    void setRingLed(byte n, byte x, byte a);
    void setRingAll(byte n, byte a);
    void setRingMap(byte n, byte d[32]);
    void setRingRange(byte n, byte x1, byte x2, byte a);
    byte switchPressed[4];
    int encCumulative[4]; // accumulated delta since initialization

    void (*keyDownCallback)(byte k);
    void (*keyUpCallback)(byte k);
    void (*encChangeCallback)(byte e, int d);
    void (*switchDownCallback)(byte e);
    void (*switchUpCallback)(byte e);
    
  private:
    USBHost _myusb;
    USBSerial _userial = USBSerial(_myusb);
    void _send1(byte b1);
    void _send2(byte b1, byte b2);
    void _send2x32(byte b1, byte b2, byte b3[32]);
    void _send3(byte b1, byte b2, byte b3);
    void _send3x8(byte b1, byte b2, byte b3, byte b4[8]);
    void _send3x32(byte b1, byte b2, byte b3, byte b4[32]);
    void _send4(byte b1, byte b2, byte b3, byte b4);
    void _send5(byte b1, byte b2, byte b3, byte b4, byte b5);

};

#endif
