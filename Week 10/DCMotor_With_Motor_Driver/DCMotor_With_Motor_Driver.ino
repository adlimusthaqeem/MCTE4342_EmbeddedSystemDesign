int directionpin = 28;
int pwmpin = 7;
void setup()
{
  // put your setup code here, to run once:
  pinMode(pwmpin, OUTPUT);
  pinMode(directionpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //stop
  digitalWrite(directionpin, HIGH);
  analogWrite(directionpin, 0);
  delay(3000);

  //move forward
  digitalWrite(dirr, HIGH);
  analogWrite(pwm,100);
  delay(3000);

  //move backward
  digitalWrite(dirr, LOW);
  analogWrite(pwm,100);
  delay(3000);
}
