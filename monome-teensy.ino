#include "TeensyGrid.h"

TeensyGrid g(16, 8);

void setup() {
  g.setup();

  g.setAllInt(0);
  int i = random(256);
  g.setRow(0,0,i);
  g.setRow(8,0,i);
  g.setCol(0,0,i);
  g.setCol(8,0,i);
  delay(1000);

  g.setAllInt(0);
  for (int x=0; x<16; x++) {
    for (int y=0; y<8; y++) {
      g.setLed(x, y, random(0,2));
      delay(10);
    }
  }
  delay(1000);
  
  g.setAllInt(0);
  for (int i=0; i<8; i++) {
    for (int j=0; j<16; j++) {
      g.setLedInt(j, i,random(16));
      delay(10);
    }
  }
  delay(1000);

  g.setAll(1);
  delay(500);
  g.setAll(0);
  delay(1000);

  g.setAllInt(0);
  for (int i=0; i<16; i++) {
    g.setAllInt(i);
    delay(40);
  }
  for (int i=15; i>=0; i--) {
   g.setAllInt(i);
   delay(40);
  }
  delay(1000);

  g.setAllInt(0);
  byte d[] = {1,2,4,8,16,32,64,128};
  g.setMap(0,0,d);
  g.setMap(8,0,d);
  delay(1000);

  g.setAllInt(0);
  byte e[] = {1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128};
  g.setLevelMap(0,0,e);
  g.setLevelMap(8,0,e);  
  delay(1000);

  g.setAllInt(0);
  byte c[] = {1,2,4,8,16,32,64,128};
  g.setLevelCol(0,0,c);
  g.setLevelRow(0,0,c);
  delay(1000);

  g.setAllInt(0);
}

void loop() {
  g.loop();
  
  for (int i=0; i<256; i++) {
    byte x = g.keyToCoords(i).x;
    byte y = g.keyToCoords(i).y;
    if (g.keyDown[i] == 1){
      Serial.print("key down: ");
      Serial.println(i);
    }
    
    if (g.keyPressed[i] == 1){
      g.setLedInt(x,y,15);
    } else {;
      g.setLedInt(x,y,0);
    }
    
    if (g.keyUp[i] == 1){
      Serial.print("key up: ");
      Serial.println(i);
    }
  }
}
