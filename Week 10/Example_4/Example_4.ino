#include "DCMotor.h"

void setup()
{
  DCMotor motor1('B', 0, 50);
  motor1.Write(0.5);
  while (1)
  {
    motor1.Refresh();
  }
}
