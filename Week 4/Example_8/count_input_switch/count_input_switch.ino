int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6; // A-E represent the 5 different swirches, Switch A to Switch E
int currentState = 0;
int previousState = 0;
int count[5];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(D, INPUT_PULLUP);
  pinMode(E, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  countUpdate(A);
  countUpdate(B);
  countUpdate(C);
  countUpdate(D);
  countUpdate(E);
  Serial.print("A = "), Serial.print(count[0]), Serial.print("   ");
  Serial.print("B = "), Serial.print(count[1]), Serial.print("   ");
  Serial.print("C = "), Serial.print(count[2]), Serial.print("   ");
  Serial.print("D = "), Serial.print(count[3]), Serial.print("   ");
  Serial.print("E = "), Serial.print(count[4]), Serial.println("   ");
}

void countUpdate(int pin)
{
  if (digitalRead(pin))
    currentState = 1;

  else
    currentState = 0;

  if (currentState != previousState)
  {
    if (currentState == 1)
      count[pin - 2] = count[pin - 2] + 1;
  }

  previousState = currentState;
  delay(250);

}
