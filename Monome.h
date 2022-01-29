#ifndef Monome_h
#define Monome_h

#include "Arduino.h"
#include "USBHost_t36.h"

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
    byte coordsToKey(coords c);
    coords keyToCoords(byte k);
    byte keyDown[256];
    byte keyPressed[256];
    byte keyUp[256];
    
  private:
    USBHost _myusb;
    USBSerial _userial = USBSerial(_myusb);
    void _send1(byte b1);
    void _send2(byte b1, byte b2);
    void _send3(byte b1, byte b2, byte b3);
    void _send4(byte b1, byte b2, byte b3, byte b4);
    void _send3x8(byte b1, byte b2, byte b3, byte b4[8]);
    void _send3x32(byte b1, byte b2, byte b3, byte b4[32]);
};

#endif