#include <SimpleRotary.h>       //Used for the rotary encoder, just need to receive the simple direction
#include <BleKeyboard.h>        //Primary heavyweight for sending keystrokes
#include <EEPROM.h>             //Used for storage of MAC address selection
#include <FastLED.h>            //Used for LEDs on keyboards - only applicable to certain Sanctuary mdoels

#include "SanctuaryHardware.h"  //Definitions file, for all the hardware - removes and simplifies from this file


//Setup memory for LEDs
// CRGB leds[NumLeds];

//Setup keyboard
// BleKeyboard Kbd("Sanctuary","Lego_Rocket",100);
BleKeyboard Kbd("Sanctuary", "LegoRocket");

// SimpleRotary rotary(Rotary1,Rotary2,40);    //Setup media rotary encoder
// byte RDir, PrevRDir;                        //Keep track of Rotary Encoder Direction

//  Code to "store" devices, so that the keyboard can switch connections on the fly ////////////////////////////////////////////////////////////////////////
//Adapted from : https://github.com/Cemu0/ESP32_USBHOST_TO_BLE_KEYBOARD/blob/main/src/USBHIDBootBLEKbd.cpp
// Primarily stores the selected MAC address in EEPROM storage
// const int maxdevice = 3;
// uint8_t MACAddress[maxdevice][6] = 
// {
//   {0x35, 0xAF, 0xA4, 0x07, 0x0B, 0x66},
//   {0x31, 0xAE, 0xAA, 0x47, 0x0D, 0x61},
//   {0x31, 0xAE, 0xAC, 0x42, 0x0A, 0x31}
  
// };

//Basically just change the selected ID and reset - MAC address can only be changed before the keyboard start, so write to store selection, until changed again
  //Take in device number, and set the EEPROM to the selected - selects what address to shift to, instead of iterating to that address
// void changeID(int DevNum)
// {
//     // Serial.println("changing MAC...");

//     //Make sure the selection is valid
//     if(DevNum < maxdevice)
//     {
//       //Write and commit to storage, reset ESP 32
//       EEPROM.write(0,DevNum);
//       EEPROM.commit();
//       //esp_reset();
//       esp_sleep_enable_timer_wakeup(1);
//       esp_deep_sleep_start(); 
//     }
// }


// uint8_t gHue = 0;                                       //Keep track of the colour wanted

//LED Function, to be expanded upon to add more LED functionality later
// void LedMode (int Select)
// {
//   switch(Select)
//   {
//     case 1:
//       gHue++;
//       fill_rainbow(leds, NumLeds, gHue, 7);
//       break;
//     case 2:
//       fill_solid(leds, NumLeds, CRGB::Cyan);      
//       break;
//     default:
//       break;
//   }
//   FastLED.show();
// }
