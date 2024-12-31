#include <BleKeyboard.h>        //Primary heavyweight for sending keystrokes
#include <Adafruit_NeoPixel.h>
#include "SanctuaryHardware.h"  //Definitions file, for all the hardware - removes and simplifies from this file

BleKeyboard Kbd("Sanctuary", "LegoRocket");
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Function to set NeoPixel color
void setNeoPixelColor(int red, int green, int blue) {
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();
}

// Method to enable NeoPixel power
void enableNeoPixelPower() {
  pinMode(NEOPIXEL_I2C_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_I2C_POWER, HIGH); // Pull power pin high to enable NeoPixel
}

// Method to initialize NeoPixel
void initializeNeoPixel() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(10); // Adjust brightness (0-255)
  pixels.show();
}