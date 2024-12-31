// DEBUG Settings
#define DEBUG 1

//Define on and off values
#define OFF 0
#define ON 1

//Pin Definitions
#define Row1 12
#define Row2 27
#define Row3 33
#define Row4 15
#define Row5 32

#define Col1 14
#define Col2 20
#define Col3 22
#define Col4 26
#define Col5 25
#define Col6 4
#define Col7 5
#define Col8 19
#define Col9 21
#define Col10 34
#define Col11 39
#define Col12 36

/*  https://learn.adafruit.com/adafruit-esp32-feather-v2/pinouts
Can use for both: 26, 25, 4, 5, 19, 21, 7, 8, 12, 27, 33, 15, 32, 14, 20, 22
Can use for Col only: 34, 39, 36, D37
Cannot use: 13 (LED)
*/

//Matrix setup
#define NumRows 5
#define NumCols 12
#define NumLayers 2

#define FUNCTION_SW   256
#define NULL_CON      257
#define NEXT          258
#define PREV          259

// NeoPixel settings
#define PIN_NEOPIXEL 0            // NeoPixel data pin
#define NEOPIXEL_I2C_POWER 2      // NeoPixel power pin
#define NUM_PIXELS 1              // Number of NeoPixels
#define NEOPIXEL_BRIGHTNESS 10    // NeoPixel brightness (0-255)
