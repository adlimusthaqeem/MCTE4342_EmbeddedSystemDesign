#include "Blinky.h"

void setup() 
{
    Blinky blinker('D', 3, 100, 200); //Blink PB5 1s ON and 1s OFF
    while (1) {
      blinker.Refresh();
    }
  }
