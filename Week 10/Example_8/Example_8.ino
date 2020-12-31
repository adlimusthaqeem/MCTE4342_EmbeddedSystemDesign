#include "DCMotor.h"
void setup()
{
  DCMotor motor('B', 0, 1000); //DC Motor attached to PB0
  PID controlsystem;
  Sensor temperature;
  while (1) {
    double input = temperture.Acquire(); //Read the value of the temp sensor
    double motor_speed = controlsystem.GetResponse(input); //Calculate response
    motor1.Write(motor_speed); //Write the output to the motor
    motor1.Refresh();
  }
}
