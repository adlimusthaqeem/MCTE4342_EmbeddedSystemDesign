//i2c Master Code(UNO)
#include <Wire.h>

void setup()
{
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);

  Wire.begin();
}

void loop()
{
  if (digitalRead(8) == HIGH)
  {
    Wire.beginTransmission(5);
    Wire.write('1');
    Wire.endTransmission();
  }
  else
  {
    Wire.beginTransmission(5);
    Wire.write('0');
    Wire.endTransmission();
  }
}

