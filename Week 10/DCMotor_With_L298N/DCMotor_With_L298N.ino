int IN1 =9;
int IN2 =12;
int ENA =10;
int IN3=5;
int IN4= 3;
int ENB=11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
forward(255,255);
delay(5000);
backward(255,255);
delay(5000);
left(200,100);
delay(5000);
right(100,200);
delay(5000);
stopp();
delay(5000);

}

void forward(int pwm_left, int pwm_right)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite (ENA, pwm_left);
  analogWrite (ENB, pwm_right);
}


void backward(int pwm_left, int pwm_right)
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite (ENA, pwm_left);
  analogWrite (ENB, pwm_right);
}


void left(int pwm_left, int pwm_right)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite (ENA, pwm_left);
  analogWrite (ENB, pwm_right);
}


void right(int pwm_left, int pwm_right)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite (ENA, pwm_left);
  analogWrite (ENB, pwm_right);
}


void stopp()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite (ENA, 0);
  analogWrite (ENB, 0);
}

