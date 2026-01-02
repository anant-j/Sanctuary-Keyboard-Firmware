// Setup, runs once on boot
void setup()
{
  Serial.begin(115200);
  if (DEBUGMODE)
  {
    Serial.println("Start Initializing...");
  }

  // Initialize NeoPixel
  initializeNeoPixel();

  // Initialize row and column pins
  initializeRowPins();
  initializeColPins();

  // Start Bluetooth keyboard
  startBluetoothKeyboard();

  // Set NeoPixel to red (searching for BT device)
  setNeoPixelColor(BluetoothDisconnectColor[0], BluetoothDisconnectColor[1], BluetoothDisconnectColor[2], BluetoothDisconnectColor[3]);
}

int RowCnt = 0;
int LayerCnt = 0;
int BluetoothAlreadyConnected = 0;
// Method to handle the loop functionality
void loop()
{
  // Check if the keyboard is connected, if so, scan the matrix
  if (Kbd.isConnected())
  {
    if (BluetoothAlreadyConnected == 0)
    {
      BluetoothAlreadyConnected = 1;
      if (DEBUGMODE)
      {
        Serial.println("Bluetooth Connected...");
      }
    }
    // Set NeoPixel to the color corresponding to the current layer
    setNeoPixelColor(LayerColors[LayerCnt][0], LayerColors[LayerCnt][1], LayerColors[LayerCnt][2], LayerColors[LayerCnt][3]);

    // Initialize new Row to scan
    digitalWrite(Rows[RowCnt], LOW);

    // Check columns
    int ColCnt = 0;

    // Repeat until all columns are scanned
    while (ColCnt <= (NumCols - 1))
    {
      // Check state of current position, and make sure it was previously off
      if (digitalRead(Cols[ColCnt]) == LOW && PressedCheck[LayerCnt][RowCnt][ColCnt] == OFF)
      {
        if (DEBUGMODE)
        {
          Serial.printf("Layer: %d, Row: %d, Col: %d, GPIO PINS: [%d,%d], KEY Pressed: %d\n", LayerCnt, RowCnt, ColCnt, Rows[RowCnt], Cols[ColCnt], AllLayers[LayerCnt][RowCnt][ColCnt]);
        }
        // Switch based on the key pressed, allows for unique functions other than alphanumerics
        switch (AllLayers[LayerCnt][RowCnt][ColCnt])
        {
        case FUNC_LAYER:
          // PressedCheck.fill(OFF);
          Kbd.releaseAll();
          if (LayerCnt < NumLayers - 1)
          {
            LayerCnt++;
          }
          else
          {
            LayerCnt = 0;
          }
          break;
        default:
          Kbd.press(AllLayers[LayerCnt][RowCnt][ColCnt]);
        }
        // Assign the current key as ON, so it doesn't constantly press the button
        PressedCheck[LayerCnt][RowCnt][ColCnt] = ON;
      }

      // Otherwise, check if the switch was released
      else if (digitalRead(Cols[ColCnt]) == HIGH && PressedCheck[LayerCnt][RowCnt][ColCnt] == ON)
      {
        // Switch based on the switch released
        switch (AllLayers[LayerCnt][RowCnt][ColCnt])
        {
        case FUNC_LAYER:
          PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
          Kbd.release(KEY_MEDIA_PLAY_PAUSE);
          Kbd.release(KEY_MEDIA_PREVIOUS_TRACK);
          Kbd.release(KEY_MEDIA_NEXT_TRACK);
          Kbd.releaseAll();
          break;
        // Release all other keys on the keyboard
        default:
          Kbd.release(AllLayers[LayerCnt][RowCnt][ColCnt]);
        }
        // Let the keyboard know it's off, and to not constantly release keys that aren't released
        PressedCheck[LayerCnt][RowCnt][ColCnt] = OFF;
      }
      // Increase column to scan
      ColCnt++;
    }
    // Reset back to original row to scan
    digitalWrite(Rows[RowCnt], HIGH);
    // Increase row outputted
    RowCnt++;
    // Loop back to original row if out of the number of rows
    if (RowCnt >= (NumRows))
    {
      RowCnt = 0;
    }
  }
  else // If the keyboard is not connected, set the NeoPixel to red
  {
    setNeoPixelColor(BluetoothDisconnectColor[0], BluetoothDisconnectColor[1], BluetoothDisconnectColor[2], BluetoothDisconnectColor[3]);
    if (BluetoothAlreadyConnected == 1)
    {
      BluetoothAlreadyConnected = 0;
      if (DEBUGMODE)
      {
        Serial.println("Bluetooth Disconnected...");
      }
    }
  }
  // Delay so it's not too fast
  delay(1);
}

// Method to initialize row output pins
void initializeRowPins()
{
  for (int i = 0; i < NumRows; i++)
  {
    if (DEBUGMODE)
    {
      Serial.print("setup row output pin: ");
      Serial.println(Rows[i]);
    }
    pinMode(Rows[i], OUTPUT);
    digitalWrite(Rows[i], HIGH);
  }
  if (DEBUGMODE)
  {
    Serial.println("setup row output pin complete...");
  }
}

// Method to initialize column input pins
void initializeColPins()
{
  for (int i = 0; i < NumCols; i++)
  {
    if (DEBUGMODE)
    {
      Serial.print("column output pin: ");
      Serial.println(Cols[i]);
    }
    pinMode(Cols[i], INPUT_PULLUP);
  }
  if (DEBUGMODE)
  {
    Serial.println("Col output pin complete...");
  }
}