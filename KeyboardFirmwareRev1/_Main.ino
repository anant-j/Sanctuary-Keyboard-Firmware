#include <Adafruit_NeoPixel.h>
#include "esp_mac.h"

// DEBUG boolean
#define DEBUG 1

// NeoPixel settings
#define PIN_NEOPIXEL 0            // NeoPixel data pin
#define NEOPIXEL_I2C_POWER 2      // NeoPixel power pin
#define NUM_PIXELS 1              // Number of NeoPixels

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Setup, runs once on boot
void setup() {  
  Serial.begin(115200);
  if(DEBUG) {
      Serial.println("Start Initializing...");
  }

  // Enable NeoPixel power
  pinMode(NEOPIXEL_I2C_POWER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(NEOPIXEL_I2C_POWER, HIGH); // Pull power pin high to enable NeoPixel

  // Initialize NeoPixel
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(10); // Adjust brightness (0-255)
  pixels.show();

  // Initialize row output pins and set default state
  for(int i = 0; i < NumRows; i++) {
    pinMode(Rows[i], OUTPUT);  
    digitalWrite(Rows[i], LOW);
    if(DEBUG) {
      Serial.print("row output pin: ");
      Serial.println(Rows[i]);
    }
  }
  if(DEBUG) {
    Serial.println("row output pin complete...");
  }

  // Initialize column pins as input, with Pulldown
  for(int i = 0; i < NumCols; i++) {
    pinMode(Cols[i], INPUT_PULLDOWN);
    if(DEBUG) {
      Serial.print("column output pin: ");
      Serial.println(Cols[i]);
    }
  }
  if(DEBUG) {
    Serial.println("Col output pin complete...");
  }
  
  // Start Bluetooth keyboard
  if(DEBUG) {
    Serial.println("kbd begin...");
  }
  Kbd.begin();
  if(DEBUG) {
    Serial.println("kbd begin complete...");
  }

  // Set NeoPixel to red (searching for BT device)
  setNeoPixelColor(255, 0, 0);
}

// Trackers for row and layer
int RowCnt = 0; 
int LayerCnt = 0;

// Loops to iterate through all functions
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  // Check if the keyboard is connected
  if(Kbd.isConnected()) {
    // Set NeoPixel to blue (connected)
    setNeoPixelColor(0, 0, 255);

    // Scan the matrix
    digitalWrite(Rows[RowCnt], HIGH);
    int ColCnt = 0;

    // Check each column
    while(ColCnt <= (NumCols - 1)) {
      // Check key press
      if(digitalRead(Cols[ColCnt]) == HIGH && PressedCheck[LayerCnt][RowCnt][ColCnt] == OFF) {
        // Process key press
        switch(Layer1[LayerCnt][RowCnt][ColCnt]) {
          case 0:
          case 1:
          case 2:
            // changeID(Layer1[LayerCnt][RowCnt][ColCnt]);
            break;
          case 3:
            Kbd.press(KEY_MEDIA_PLAY_PAUSE);
            break;
          case 5:
            ESP.restart();
            break;
          case FUNCTION_SW:
            Kbd.releaseAll();
            LayerCnt++;
            break;
          case NULL_CON:
            break;
          case NEXT:
            Kbd.press(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case PREV:
            Kbd.press(KEY_MEDIA_PREVIOUS_TRACK);
            break;
          default:
            Kbd.press(Layer1[LayerCnt][RowCnt][ColCnt]);
        }
        PressedCheck[LayerCnt][RowCnt][ColCnt] = ON;   
      } 
      // Check key release
      else if(digitalRead(Cols[ColCnt]) == LOW && PressedCheck[LayerCnt][RowCnt][ColCnt] == ON) {
        // Reset NeoPixel to blue (connected)
        setNeoPixelColor(0, 0, 255);

        // Process key release
        switch(Layer1[LayerCnt][RowCnt][ColCnt]) {
          case 0:
          case 1:
          case 2:
            break;
          case 3:
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);
            break;
          case FUNCTION_SW:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            if(LayerCnt > 0) {
              LayerCnt--;
            }
            Kbd.releaseAll();
            break;
          case NULL_CON:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            if(LayerCnt > 0) {
              LayerCnt--;
            }
            Kbd.releaseAll();
            break;
          case NEXT:
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            break;
          case PREV:
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            break;
          default:
            Kbd.release(Layer1[LayerCnt][RowCnt][ColCnt]);
        }
        PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
      }
      ColCnt++;
    }
    digitalWrite(Rows[RowCnt], LOW);
    RowCnt++;
    if(RowCnt >= (NumRows)) {
      RowCnt = 0;
    }
  } else {
    // Set NeoPixel to red (searching for BT device)
    setNeoPixelColor(255, 0, 0);
  }

  delay(1);
}

// Function to set NeoPixel color
void setNeoPixelColor(int red, int green, int blue) {
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();
}
