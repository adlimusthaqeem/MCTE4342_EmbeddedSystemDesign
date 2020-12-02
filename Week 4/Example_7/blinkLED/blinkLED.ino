int led1 = 8;
int led2 = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);
  delay(750);
  digitalWrite(led1, LOW);
  delay(350);
  digitalWrite(led2, HIGH);
  delay(400);
  digitalWrite(led2, LOW);
  delay(600);
}
