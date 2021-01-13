void setup() 
{
  pinMode(8, INPUT_PULLUP); // set push button pin as input
  Serial.begin(9600);       // initialize UART with baud rate of 9600 bps
}

void loop() 
{
  if (digitalRead(8) == HIGH) Serial.write('0');    // send the char '0' to serial if button is not pressed.
  else Serial.write('1');                           // send the char '1' to serial if button is pressed.
}
