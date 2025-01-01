// Rows to scan, and Columns to read (definitions in SanctuaryHardware
short Rows[NumRows] = {Row1, Row2, Row3, Row4, Row5};
short Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9, Col10, Col11, Col12};

//  Layer 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AllLayers[NumLayers][NumRows][NumCols] =
    {
        {
            {FUNC_LAYER, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
            {FUNC_LAYER, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
            {FUNC_LAYER, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
            {FUNC_LAYER, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
            {FUNC_LAYER, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
        },
        {
            {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
            {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
            {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
            {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
            {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        },
};

// define a map to store different colors/rgb for different layers
// defined as {R, G, B, Brightness}
int BluetoothDisconnectColor[4] = {255, 0, 0, 10}; // Red
int LayerColors[NumLayers][4] = {
    {0, 255, 0, 5}, // Green
    {0, 0, 255, 5}, // Blue
};

// Array to check if a key is currently pressed - Initiate everything to 0
short PressedCheck[NumLayers][NumRows][NumCols] = {OFF};
