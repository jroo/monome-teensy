# monome-teensy

allows [teensy development boards](https://www.pjrc.com/teensy/) to communicate with monome grids via [monome serial protocol](https://monome.org/docs/serialosc/serial.txt)

- works with teensy 3.6, 4.0 and 4.1 (when usb host is configured)
- designed for varibright 128 grids 
- experimenetal support for monobright, 64 and 256 grids

monome-teensy is a library that allows teensy devices configured as usb hosts to communicate with monome devices via usb serial. it uses the [USBHost_t36 library](https://github.com/PaulStoffregen/USBHost_t36) and works with teensy development boards 3.6, 4.0 and 4.1.

the library is designed to work with all monome grids but has only been tested on a varibright 128 grid. to date it hasn't been confirmed to work with other grids but there's no reason it shouldn't work.

see monome-teensy.ino for examples

### functionality: grid

the functions available in the library are:

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

### grid example

create the Monome object

```c
#include "Monome.h"

Monome m;
```

add monome setup to your sketch

```c
void setup()
{
  m.setup();
}
```

add monome loop to your sketch

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

### to do:
- more documentation
- sys commands
- arc support
- support multiple devices at once
- tilt support
