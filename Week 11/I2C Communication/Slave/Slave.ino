//i2c Slave(LEONARDO)
#include <Wire.h>
int x = 0;

void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  pinMode(13, OUTPUT);      // set LED pin as output
  digitalWrite(13, LOW);    // switch off LED pin
}

void loop()
{

}

void receiveEvent()
{
  while (Wire.available())
  {
    char c = Wire.read();

    if (c == '1')
    {
      digitalWrite(13, HIGH);
      
    }
    else if (c == '0')
    {
      digitalWrite(13, LOW);
    }
  }
}
