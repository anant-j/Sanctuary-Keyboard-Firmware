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
  Kbd.begin();
  if(DEBUG) {
    Serial.println("kbd begin complete...");
  }
}

int RowCnt = 0; 
int LayerCnt = 0;
// Method to handle the loop functionality
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 

  if(Kbd.isConnected()) {
    // Set NeoPixel to blue (connected)
    setNeoPixelColor(0, 0, 255);
    // Scan the matrix
    scanMatrix();
  } else {
    // Set NeoPixel to red (searching for BT device)
    setNeoPixelColor(255, 0, 0);
  }

  delay(1);
}

// Method to scan the matrix and handle key presses
void scanMatrix() {
  digitalWrite(Rows[RowCnt], HIGH);
  int ColCnt = 0;

  // Check each column
  while(ColCnt <= (NumCols - 1)) {
    // Handle key press
    if(digitalRead(Cols[ColCnt]) == HIGH && PressedCheck[LayerCnt][RowCnt][ColCnt] == OFF) {
      handleKeyPress(ColCnt);
    } 
    // Handle key release
    else if(digitalRead(Cols[ColCnt]) == LOW && PressedCheck[LayerCnt][RowCnt][ColCnt] == ON) {
      handleKeyRelease(ColCnt);
    }
    ColCnt++;
  }
  digitalWrite(Rows[RowCnt], LOW);
  RowCnt++;
  if(RowCnt >= (NumRows)) {
    RowCnt = 0;
  }
}

// Method to handle key press events
void handleKeyPress(int ColCnt) {
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

// Method to handle key release events
void handleKeyRelease(int ColCnt) {
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
