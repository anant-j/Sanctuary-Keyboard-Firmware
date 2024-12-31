// Setup, runs once on boot
void setup() {  
  Serial.begin(115200);
  if(DEBUG) {
      Serial.println("Start Initializing...");
  }

  // Enable NeoPixel power
  enableNeoPixelPower();

  // Initialize NeoPixel
  initializeNeoPixel();

  // Initialize row and column pins
  initializeRowPins();
  initializeColPins();

  // Start Bluetooth keyboard
  startBluetoothKeyboard();

  // Set NeoPixel to red (searching for BT device)
  setNeoPixelColor(255, 0, 0);
}

// Method to initialize row output pins
void initializeRowPins() {
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
}

// Method to initialize column input pins
void initializeColPins() {
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
}

// Method to start Bluetooth keyboard
void startBluetoothKeyboard() {
  if(DEBUG) {
    Serial.println("kbd begin...");
  }
  Kbd.releaseAll();
  Kbd.end();
  Kbd.begin();
  if(DEBUG) {
    Serial.println("kbd setup complete...");
  }
}

int RowCnt = 0; 
int LayerCnt = 0;
// Method to handle the loop functionality
void loop() {
  //Check if the keyboard is connected, if so, scan the matrix
  if(Kbd.isConnected())
  {
    if (LayerCnt == 0){
      // Set NeoPixel to green (connected layer 1)
      setNeoPixelColor(0, 255, 0);
    }
    else if (LayerCnt == 1){
      // Set NeoPixel to blue (connected layer 2)
      setNeoPixelColor(0, 0, 255);
    }
    else {
      // Set NeoPixel to white (connected layer) 
      setNeoPixelColor(255, 255, 255);
    }

    //Initialize new Row to scan
    digitalWrite(Rows[RowCnt],HIGH);
    
    //Check columns
    int ColCnt = 0;

    //Repeat until all columns are scanned
    while(ColCnt <= (NumCols - 1))
    {
      //Check state of current position, and make sure it was previously off
      if(digitalRead( Cols[ColCnt] ) == HIGH && PressedCheck[LayerCnt][RowCnt][ColCnt] == OFF)
      {
        //Switch based on the key pressed, allows for unique functions other than alphanumerics
        switch(AllLayers[LayerCnt][RowCnt][ColCnt])
        {
          //Change the ID of the bluetooth, so you can connect to another device
          case 0:
          case 1:
          case 2:
            // changeID(AllLayers[LayerCnt][RowCnt][ColCnt]);
            break;
          //Rotary encoder button, play pause not an int
          case 3:
            Kbd.press(KEY_MEDIA_PLAY_PAUSE);
            break;
          //All other buttons are pressed through the Layer array
          case 5:
            ESP.restart();
            break;
          case FUNCTION_SW:
            //PressedCheck.fill(OFF);
            Kbd.releaseAll();
            if (LayerCnt < NumLayers - 1){
            LayerCnt++;
            }
            else {
              LayerCnt = 0;
            }
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
            Kbd.press( AllLayers[LayerCnt][RowCnt][ColCnt] );
        }
        //Assign the current key as ON, so it doesn't constantly press the button
        PressedCheck[LayerCnt][RowCnt][ColCnt] = ON;   
        //Serial.print( AllLayers[a][ColCnt] );
      }

      //Otherwise, check if the switch was released
      else if(digitalRead( Cols[ColCnt] ) == LOW && PressedCheck[LayerCnt][RowCnt][ColCnt] == ON)
      {
        //Switch based on the switch released
        switch(AllLayers[LayerCnt][RowCnt][ColCnt])
        {
          //Nothing for the tactile switch
          case 1:
          case 2:
          case 0:
            break;
          //Release the rotary encoder button
          case 3:
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);
            break;
          case FUNCTION_SW:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            // if(LayerCnt > 0)
            // {
            //   LayerCnt--;
            // }
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);            
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case NULL_CON:
            PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
            // if(LayerCnt > 0)
            // {
            //   LayerCnt--;
            // }
            Kbd.release(KEY_MEDIA_PLAY_PAUSE);            
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            Kbd.releaseAll();
            break;
          case NEXT:
            Kbd.release(KEY_MEDIA_NEXT_TRACK);
            break;
          case PREV:
            Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
            break;
          //Release all other keys on the keyboard
          default:
            Kbd.release( AllLayers[LayerCnt][RowCnt][ColCnt] );
        }
        //Let the keyboard know it's off, and to not constantly release keys that aren't released
        PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
      }
      //Increase column to scan
      ColCnt++;
    }
    //Reset back to original row to scan
    digitalWrite(Rows[RowCnt],LOW);
    //Increase row outputted
    RowCnt++;
    //Loop back to original row if out of the number of rows
    if(RowCnt >= (NumRows))
    {
      RowCnt = 0;
    }
  }

  //Delay so it's not too fast
  delay(1);
}