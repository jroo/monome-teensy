#include "TeensyGrid.h"

TeensyGrid::TeensyGrid(byte cols, byte rows)
{
  _cols = cols;
  _rows = rows;
}

void TeensyGrid::setup()
{
  _myusb.begin();
  _userial.begin(115200);
  Serial.begin(115200);
}

void TeensyGrid::loop() 
{
  _myusb.Task();
}

void TeensyGrid::setOverallInt(byte i)
{
  // change overall led intensity
  _send2(0x17, (byte)i);
}

void TeensyGrid::setLed(byte x, byte y, byte s)
{
  // set led state
  _send3(0x10 + s, x, y);
}

void TeensyGrid::setLedInt(byte x, byte y, byte i) 
{
  // set individual led intensity
  _send4(0x18, x, y, i);
}

void TeensyGrid::setAll(byte s)
{
  _send1(0x12 + s);
}

void TeensyGrid::setAllInt(byte i)
{
  // set all leds to intensity i
  _send2(0x19, i);
}

void TeensyGrid::setRow(byte x, byte y, byte d)
{
  _send4(0x15, x, y, d);
  delay(5);
}

void TeensyGrid::setLevelRow(byte x, byte y, byte d[8])
{
  _send3x8(0x1B, x, y, d);
  delay(5);
}

void TeensyGrid::setLevelCol(byte x, byte y, byte d[8])
{
  _send3x8(0x1C, x, y, d);
  delay(5);
}

void TeensyGrid::setCol(byte x, byte y, byte d)
{
  _send4(0x16, x, y, d); 
  delay(5);
}

void TeensyGrid::setMap(byte x, byte y, byte d[8])
{
  _send3x8(0x14, x, y, d);
}

void TeensyGrid::setLevelMap(byte x, byte y, byte d[32])
{
  _send3x32(0x1A, x, y, d);
}

void TeensyGrid::_send1(byte b1)
{
  _userial.write(b1);
  _userial.flush();
}

void TeensyGrid::_send2(byte b1, byte b2)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.flush(); 
}

void TeensyGrid::_send3(byte b1, byte b2, byte b3)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  _userial.flush(); 
}

void TeensyGrid::_send4(byte b1, byte b2, byte b3, byte b4)
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  _userial.write(b4);
  _userial.flush(); 
}

void TeensyGrid::_send3x8(byte b1, byte b2, byte b3, byte b4[8])
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  for (int i=0; i<8; i++) {
    _userial.write(b4[i]);
  }
  _userial.flush();
}

void TeensyGrid::_send3x32(byte b1, byte b2, byte b3, byte b4[32])
{
  _userial.write(b1);
  _userial.write(b2);
  _userial.write(b3);
  for (int i=0; i<32; i++) {
    _userial.write(b4[i]);
  }
  _userial.flush();
}
