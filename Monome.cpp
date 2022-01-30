#include "Monome.h"

Monome::Monome() {}

void Monome::setup()
{
  _myusb.begin();
  _userial.begin(115200);
  Serial.begin(115200);

  //initialize keys
  for (byte y=0; y<16; y++) {
    for (byte x=0; x<16; x++) {
      coords c = {x, y};
      byte k = coordsToKey(c);
      keyDown[k] = 0;
      keyUp[k] = 0;
      keyPressed[k] = 0;
    }
  }

  //initialize encoders
  for (byte e=0; e<4; e++) {
    encoderPos[e] = 0;
    switchDown[e] = 0;
    switchPressed[e] = 0;
    switchUp[e] = 0;
  }
}

void Monome::loop() 
{
  // clear key status to allow for checking again this iteration
  for (int i=0; i<256; i++) {
    keyDown[i] = 0;
    keyUp[i] = 0;
  }

  // clear switch status to allow for checking again
  for (int i=0; i<4; i++) {
    switchDown[i] = 0;
    switchUp[i] = 0;
  }
  
  _myusb.Task();

  // handle messages from monome device
  while (_userial.available()) {
    if (_userial.peek() == 33) {
      //handle key down message 0x21
      _userial.read(); //throw away first byte
      byte x = _userial.read();
      byte y = _userial.read();
      coords c = {x, y};
      byte k = coordsToKey(c);
      keyDown[k] = 1;
      keyPressed[k] = 1;
      _userial.flush();
    } else if (_userial.peek() == 32) {
      //handle key up down message 0x20
      _userial.read();
      byte x = _userial.read();
      byte y = _userial.read();
      coords c = {x, y};
      byte k = coordsToKey(c);
      keyUp[k] = 1;
      keyPressed[k] = 0;
      _userial.flush();
    } else if (_userial.peek() == 80) {
      //handle encoder change 0x50
      _userial.read();
      byte e = _userial.read();
      int8_t d = _userial.read();
      encoderPos[e] += d;
      _userial.flush();
    } else if (_userial.peek() == 81) {
      //handle encoder switch up 0x51
      _userial.read();
      byte e = _userial.read();
      switchUp[e] = 1;
      switchPressed[e] = 0;
      _userial.flush();
    } else if (_userial.peek() == 82) {
      //handle encoder switch down 0x52
      _userial.read();
      byte e = _userial.read();
      switchDown[e] = 1;
      switchPressed[e] = 1;
      _userial.flush();
    }
  }
}

void Monome::setOverallInt(byte i)
{
  // change overall led intensity
  _send2(0x17, (byte)i);
}

void Monome::setLed(byte x, byte y, byte s)
{
  // set led state
  _send3(0x10 + s, x, y);
}

void Monome::setLedInt(byte x, byte y, byte i) 
{
  // set individual led intensity
  _send4(0x18, x, y, i);
}

void Monome::setAll(byte s)
{
  _send1(0x12 + s);
}

void Monome::setAllInt(byte i)
{
  // set all leds to intensity i
  _send2(0x19, i);
}

void Monome::setRow(byte x, byte y, byte d)
{
  _send4(0x15, x, y, d);
  delay(5);
}

void Monome::setLevelRow(byte x, byte y, byte d[8])
{
  _send3x8(0x1B, x, y, d);
  delay(5);
}

void Monome::setLevelCol(byte x, byte y, byte d[8])
{
  _send3x8(0x1C, x, y, d);
  delay(5);
}

void Monome::setCol(byte x, byte y, byte d)
{
  _send4(0x16, x, y, d); 
  delay(5);
}

void Monome::setMap(byte x, byte y, byte d[8])
{
  _send3x8(0x14, x, y, d);
}

void Monome::setLevelMap(byte x, byte y, byte d[32])
{
  _send3x32(0x1A, x, y, d);
}

void Monome::setRingLed(byte n, byte x, byte a) 
{
  _send4(0x90, n, x, a);
}

void Monome::setRingAll(byte n, byte a)
{
  _send3(0x91, n, a);
}

void Monome::setRingMap(byte n, byte d[32])
{
  _send2x32(0x92, n, d);
}

void Monome::setRingRange(byte n, byte x1, byte x2, byte a)
{
  _send5(0x93, n, x1, x2, a);
}

void Monome::_send1(byte b1)
{
  _userial.write(b1);
  _userial.flush();
}

void Monome::_send2(byte b1, byte b2)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.flush(); 
}

void Monome::_send2x32(byte b1, byte b2, byte b3[32])
{
  _userial.write(b1);
  _userial.write(b2);
  for (int i=0; i<32; i++) {
    _userial.write(b3[i]);
  }
  _userial.flush();
}

void Monome::_send3(byte b1, byte b2, byte b3)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  _userial.flush(); 
}

void Monome::_send3x8(byte b1, byte b2, byte b3, byte b4[8])
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  for (int i=0; i<8; i++) {
    _userial.write(b4[i]);
  }
  _userial.flush();
}

void Monome::_send3x32(byte b1, byte b2, byte b3, byte b4[32])
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  for (int i=0; i<32; i++) {
    _userial.write(b4[i]);
  }
  _userial.flush();
}

void Monome::_send4(byte b1, byte b2, byte b3, byte b4)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  _userial.write(b4);
  _userial.flush(); 
}

void Monome::_send5(byte b1, byte b2, byte b3, byte b4, byte b5)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  _userial.write(b4);
  _userial.write(b5);
  _userial.flush(); 
}

byte Monome::coordsToKey(coords c)
{
  return (c.y * 16) + c.x;
}

coords Monome::keyToCoords(byte k)
{
  byte x = k % 16;
  byte y = byte(k / 16);
  coords c = {x, y};
  return c;
}
