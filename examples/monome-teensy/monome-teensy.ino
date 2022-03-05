#include <Monome.h>

Monome m;

void setup() 
{
  Serial.begin(115200);
  
  m.setup();
  m.keyDownCallback = &kDown;
  m.keyUpCallback = &kUp;
  m.encChangeCallback = &eChg;
  m.switchDownCallback = &sDown;
  m.switchUpCallback = &sUp;
  
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
    
    if (m.keyPressed[i] == 1){
      m.setLedInt(x,y,15);
    } else {;
      m.setLedInt(x,y,0);
    }
  }
}

void kDown(byte k) {
  Serial.print("Key Down: ");
  Serial.println(k);
}

void kUp(byte k) {
  Serial.print("Key Up: ");
  Serial.println(k);
}

void eChg(byte e, int d) {
  Serial.println("Encoder Change");
}

void sDown(byte e) {
  Serial.println("Switch Down");
}

void sUp(byte e) {
  Serial.println("Switch Up");
}
