#include <SPI.h>
short yawAngle;
short setYawAngle;

void mpuRead ()
{
  digitalWrite(SS, LOW);
  transferAndWait (0);
  yawAngle = transferAndWait (0);
  //yawAngle += transferAndWait (0);
  digitalWrite(SS, HIGH);
}

byte transferAndWait (const byte what)
{
  int a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} // end of transferAndWait
void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  digitalWrite(SS, HIGH);  // ensure SS stays high for now
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  // put your main code here, to run repeatedly:
  mpuRead();
  Serial.println(yawAngle);
}
