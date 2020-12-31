#include "DCMotor.h"
void setup()
{
  DCMotor motor1('B', 0, 1000);
  motor1.Write(0.2);
  while (1) {
    motor1.Refresh();
  }
}
