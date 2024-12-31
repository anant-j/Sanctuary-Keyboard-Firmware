//Rows to scan, and Columns to read (definitions in SanctuaryHardware
short Rows[NumRows] = {Row1, Row2 , Row3, Row4, Row5};
short Cols[NumCols] = {Col1, Col2, Col3, Col4, Col5, Col6, Col7, Col8, Col9, Col10, Col11, Col12 };

//  Layer 1 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AllLayers[NumLayers][NumRows][NumCols] = 
{
  {
    {FUNCTION_SW,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u',      'i', 'o'   ,       'p'   ,       '[' },
    {FUNCTION_SW,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u',      'i', 'o'   ,       'p'   ,       '[' },    
    {FUNCTION_SW,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u',      'i', 'o'   ,       'p'   ,       '[' },
    {FUNCTION_SW,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u',      'i', 'o'   ,       'p'   ,       '[' },
    {FUNCTION_SW,       'q'   ,       'w'   ,       'e'   ,       'r'   ,       't'   ,       'y'   ,       'u',      'i', 'o'   ,       'p'   ,       '[' },
  },
  {
    {FUNCTION_SW,       'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j',      'k', 'l'   ,       ';'   ,       'z' },
    {FUNCTION_SW,       'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j',      'k', 'l'   ,       ';'   ,       'z' }, 
    {FUNCTION_SW,       'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j',      'k', 'l'   ,       ';'   ,       'z' },
    {FUNCTION_SW,       'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j',      'k', 'l'   ,       ';'   ,       'z' },
    {FUNCTION_SW,       'a'   ,       's'   ,       'd'   ,       'f'   ,       'g'   ,       'h'   ,       'j',      'k', 'l'   ,       ';'   ,       'z' }, 
  },
};

//Array to check if a key is currently pressed - Initiate everything to 0
short PressedCheck[NumLayers][NumRows][NumCols] = { OFF };
