# monome-teensy

allows [teensy development boards](https://www.pjrc.com/teensy/) to communicate with monome grids via [monome serial protocol](https://monome.org/docs/serialosc/serial.txt)

- works with teensy 3.6, 4.0 and 4.1 (when usb host is configured)
- designed for varibright 128 grids 
- experimental support for monobright, 64 and 256 grids
- experimental support for arc

monome-teensy is a library that allows teensy devices configured as usb hosts to communicate with monome devices via usb serial. it uses the [USBHost_t36 library](https://github.com/PaulStoffregen/USBHost_t36) and works with teensy development boards 3.6, 4.0 and 4.1.

the library is designed to work with all monome grids but has only been tested on a varibright 128 grid. to date it hasn't been confirmed to work with other grids but there's no reason it shouldn't work. there is also experimental support for arc but it's untested since i'll probably never have an arc.

see monome-teensy.ino for examples

### functionality: grid

grid functions available in the library are:

```c
setOverallInt();  // set overall intensity of grid
setLed();         // set individual led on or off
setLedInt();      // set intensity of individual led
setAll();         // set all leds on or off
setAllInt();      // set intensity of all leds
setRow();         // set an 8x1 row on or off
setLevelRow();    // set intensity of an 8x1 row
setCol();         // set a 1x8 col on or off
setLevelCol();    // set intensity of 1x8 col
setMap();         // set individual leds in 8x8 grid on or off
setLevelMap();    // set level of individual leds in 8x8 grid
```

arrays to store the status of grid keys:

```c
keyPressed[256];  // true if key is being held down
keyDown[256];     // true if key down message received
keyUp[256];       // true if key up message received
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

this example will light up a key when pressed and send serial messages on key up or down

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
setRingLed();   // sets individual led
setRingAll();   // sets all leds
setRingMap();   // sets individual values for all leds
setRingRange(); // sets individual values for a range of leds
```

arrays to store the status of the encoders and their respective switches:

```c
switchPressed[4]; // true if switch is being held down  
switchDown[4];    // true if switch down message received
switchUp[4];      // true if switch up message received
encDelta[4];      // delta value sent from serial
encCumulative[4]; // cumulative tally of encoder deltas since initialization
```

### to do:
- use proper directory structure for a teensy lib
- sys commands
- support multiple devices at once
- tilt support
