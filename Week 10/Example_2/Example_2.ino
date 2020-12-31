#include "Blinky.h"

void setup() 
{
    Blinky blinker('B', 5, 200, 300); //Blink PB5 1s ON and 1s OFF
    while (1) {
      blinker.Refresh();
    }
  }
