// Rows to scan, and Columns to read (definitions in SanctuaryHardware
short Rows[NumRows] = {Row1, Row2, Row3, Row4, Row5, Row6};
short Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9, Col10, Col11, Col12, Col13, Col14, Col15, Col16, Col17, Col18};

//  Layer 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AllLayers[NumLayers][NumRows][NumCols] =
    {
        {
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
            {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},                        
        }
        // {
        //     {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        //     {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        //     {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        //     {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        //     {FUNC_LAYER, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'},
        // },
};

// define a map to store different colors/rgb for different layers
// defined as {R, G, B, Brightness}
int BluetoothDisconnectColor[4] = {255, 0, 0, 10}; // Red
int LayerColors[NumLayers][4] = {
    {0, 255, 0, 5}, // Green
    // {0, 0, 255, 5}, // Blue
};

// Array to check if a key is currently pressed - Initiate everything to 0
short PressedCheck[NumLayers][NumRows][NumCols] = {OFF};
