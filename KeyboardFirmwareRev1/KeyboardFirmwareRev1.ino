#include <BleKeyboard.h>        //Primary heavyweight for sending keystrokes
#include <Adafruit_NeoPixel.h>
#include "SanctuaryHardware.h"  //Definitions file, for all the hardware - removes and simplifies from this file

BleKeyboard Kbd("Sanctuary", "LegoRocket");
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
