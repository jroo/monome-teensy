# monome-teensy

allows [teensy development boards](https://www.pjrc.com/teensy/) to communicate with monome grids via [monome serial protocol](https://monome.org/docs/serialosc/serial.txt)

- works with teensy 3.6, 4.0 and 4.1 (when usb host is configured)
- designed for varibright 128 grids 
- experimenetal support for monobright, 64 and 256 grids

monome-teensy is a library that allows teensy devices configured as usb hosts to communicate with monome devices via usb serial. it uses the [USBHost_t36 library](https://github.com/PaulStoffregen/USBHost_t36) and works with teensy development boards 3.6, 4.0 and 4.1.

the library is designed to work with all monome grids but has only been tested on a varibright 128 grid. to date it hasn't been confirmed to work with other grids but there's no reason it shouldn't work.

see monome-teensy.ino for examples

### functionality: grid

grid functions available in the library are:

```c
setOverallInt();
setLed();
setLedInt();
setAll();
setAllInt();    
setRow();
setLevelRow();
setCol();
setLevelCol();
setMap();
setLevelMap();
```

arrays to store the status of grid keys:

```c
keyDown[256];
keyPressed[256];
keyUp[256];
```

### led-grid example

let's create a sketch that by sets the intensity of all leds in a grid to zero then gradually increases and decreases the intensity

first, create the `Monome` object

```c
#include "Monome.h"

Monome m;
```

add the `setup()` function of your `Monome` object to your sketch's `setup()` 

```c
void setup()
{
  m.setup();
}
```

add the `loop()` function of your `Monome` object to your sketch's `loop()`

```c
void loop()
{
  m.loop();
}
```

update your loop code to make all grid leds pulse

```c
void loop()
{
  m.loop();

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
}
```

### key-grid example

```c
#include "Monome.h"

Monome m;

void setup()
{
  m.setup();
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
```

### arc support

_arc support is *experimental* since i don't have an arc to test this with_

arc functions:

```c
setRingLed();
setRingAll();
setRingMap();
setRingRange();
```

arrays to store the status of the encoders and their respective switches:

```c
switchDown[4];
switchPressed[4];
switchUp[4];
encoderPos[4];
```

### to do:
- sys commands
- support multiple devices at once
- tilt support
