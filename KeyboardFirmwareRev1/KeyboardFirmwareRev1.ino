#include <BleKeyboard.h> //Primary heavyweight for sending keystrokes
#include <Adafruit_NeoPixel.h>
#include "SanctuaryHardware.h" //Definitions file, for all the hardware - removes and simplifies from this file

BleKeyboard Kbd("Sanctuary", "WirelessSplit60", 101);
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// ------------------------NEOPIXEL SETUP--------------------------------
// Function to set NeoPixel color
void setNeoPixelColor(int red, int green, int blue, int brightness)
{
  pixels.setBrightness(brightness);
  pixels.setPixelColor(PIN_NEOPIXEL, pixels.Color(red, green, blue));
  pixels.show();
}

// Method to initialize NeoPixel
void initializeNeoPixel()
{
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(NEOPIXEL_BASE_BRIGHTNESS); // Adjust brightness (0-255)
  pixels.show();
}

// ------------------------BT SETUP--------------------------------
// Method to start Bluetooth keyboard
void startBluetoothKeyboard()
{
  if (DEBUGMODE)
  {
    Serial.println("BLE KBD setup begin...");
  }
  Kbd.releaseAll();
  Kbd.end();
  Kbd.begin();
  if (DEBUGMODE)
  {
    Serial.println("BLE KBD setup complete...");
  }
}
