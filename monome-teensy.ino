#include "Monome.h"

Monome m;

void setup() 
{
  m.setup();

  m.setAllInt(0);
  int i = random(256);
  m.setRow(0,0,i);
  m.setRow(8,0,i);
  m.setCol(0,0,i);
  m.setCol(8,0,i);
  delay(1000);

  m.setAllInt(0);
  for (int x=0; x<16; x++) {
    for (int y=0; y<8; y++) {
      m.setLed(x, y, random(0,2));
      delay(10);
    }
  }
  delay(1000);
  
  m.setAllInt(0);
  for (int i=0; i<8; i++) {
    for (int j=0; j<16; j++) {
      m.setLedInt(j, i,random(16));
      delay(10);
    }
  }
  delay(1000);

  m.setAll(1);
  delay(500);
  m.setAll(0);
  delay(1000);

  m.setAllInt(0);
  for (int i=0; i<16; i++) {
    m.setAllInt(i);
    delay(40);
  }
  for (int i=15; i>=0; i--) {
   m.setAllInt(i);
   delay(40);
  }
  delay(1000);

  m.setAllInt(0);
  byte d[] = {1,2,4,8,16,32,64,128};
  m.setMap(0,0,d);
  m.setMap(8,0,d);
  delay(1000);

  m.setAllInt(0);
  byte e[] = {1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128};
  m.setLevelMap(0,0,e);
  m.setLevelMap(8,0,e);  
  delay(1000);

  m.setAllInt(0);
  byte c[] = {1,2,4,8,16,32,64,128};
  m.setLevelCol(0,0,c);
  m.setLevelRow(0,0,c);
  delay(1000);

  m.setAllInt(0);
}

void loop() 
{
  m.loop();

  for (int i=0; i<256; i++) {
    byte x = m.keyToCoords(i).x;
    byte y = m.keyToCoords(i).y;
    if (m.keyDown[i] == 1){
      Serial.print("key down: ");
      Serial.println(i);
    }
    
    if (m.keyPressed[i] == 1){
      m.setLedInt(x,y,15);
    } else {;
      m.setLedInt(x,y,0);
    }
    
    if (m.keyUp[i] == 1){
      Serial.print("key up: ");
      Serial.println(i);
    }
  }
}
