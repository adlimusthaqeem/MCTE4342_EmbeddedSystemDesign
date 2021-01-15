//******************SPI Communication Protocol************************//
#include <SPI.h>

//******************LCD I2C Protocol************************//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//******************Servo Motor Setup************************//
#include <Servo.h>
Servo myservo;

//******************Timer One Interrupt************************//
#include <TimerOne.h>

#define startbutton 4
#define playbutton 2
#define led 3

short yawAngle; //value for current angle orientation
int test1 = 1, test2 = 1, startGame = 0;
int target[10]; //array to store the target angle in 10 different rounds.
int enemy[10];  //array to store number of enemies in 10 different rounds.
int mapp;       //to store the angle of the gyrosensor after mapping process from 0-255 to 0-180

//function to store retrieved gyrosensor reading from Arduino Nano to Arduino Mega
void mpuRead ()
{
  digitalWrite(SS, LOW);
  transferAndWait (0);
  yawAngle = transferAndWait (0);
  //yawAngle += transferAndWait (0);
  digitalWrite(SS, HIGH);
}

//function to retrieve gyrosensor reading from Arduino Nano to Arduino Mega
byte transferAndWait (const byte what)
{
  int a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} // end of transferAndWait

void setup()
{
  Serial.begin (115200);
  digitalWrite(SS, HIGH);             // ensure SS stays high for now
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV8);// Slow down the master a bit

  pinMode(playbutton, INPUT);  //playbutton as input
  pinMode(led, OUTPUT);        //led as output
  pinMode(startbutton, INPUT); //startbutton as input
  myservo.attach(9);           //servo at pin digital 9

  lcd.begin();
  lcd.backlight();

  randomSeed(analogRead(0));    //enable random number generator

  Timer1.initialize(100000);    //initialize Timer 1 interrupt to run every 0.1 seconds
  Timer1.attachInterrupt(Read); //read gyrosensor and move servo every 0.1 seconds
}

void loop()
{
  startGame = digitalRead(startbutton);

  if ((startGame == 0)) //startGame mode is 0
  {
    intro(); //go to intro function
  }

  if ((startGame == 1)) //startGame mode is 1
  {
    //display lcd to tell player to get ready
    lcd.clear();
    lcd.print("Are you ready?");
    delay(2000);
    lcd.clear();
    lcd.print("Concentrate!!");
    delay(2000);
    lcd.clear();
    lcd.print("GO!!");
    delay(2000);

    //generate random number for the target and number of enemies
    while (test1)
    {
      for (int i = 0; i < 10; i++)
      {
        target[i] = {random(1, 180)};
        enemy[i] = {random(5, 10)};
      }
      test1 = 0;
    }

    //Game is ongoing from Round 1 to Round 10
    for (int h = 0; h < 10; h++)
    {
      while ((enemy[h] != 0)) //while the enemy is present, the round will remain the same. Next round will activated once all enemy executed.
      {
        while ( (mapp != (target[h])) && (enemy[h] != 0)) //display the info everytime even the angle is not met and there is still enemy left
        {
          lcd.clear();
          lcd.setCursor(8, 0);
          lcd.print("ENEMY:");
          lcd.print(enemy[h]);
          lcd.setCursor(10, 1);
          lcd.print("RND:");
          lcd.print(h + 1);
          lcd.setCursor(0, 0);
          lcd.print(mapp);
          lcd.setCursor(0, 1);
          lcd.print("TARGET:");
          lcd.print(target[h]);
          delay(100);
          digitalWrite(3, LOW);
        }

        while ( mapp == (target[h])) //run this if the angle in line with the target angle
        {
          lcd.clear();
          lcd.setCursor(8, 0);
          lcd.print("ENEMY:");
          lcd.print(enemy[h]);
          lcd.setCursor(10, 1);
          lcd.print("RND:");
          lcd.print(h + 1);
          lcd.setCursor(0, 0);
          lcd.print(mapp);
          lcd.setCursor(0, 1);
          lcd.print("TARGET:");
          lcd.print(target[h]);
          delay(100);
          if ((enemy[h] != 0)) //run this if the angle is in line AND enemy is there
          {
            if ((digitalRead(playbutton) == 1)) //shoot enemy only possible when in the right angle.
            {
              digitalWrite(led, HIGH); //light up LED if shooting/play button pressed
              enemy[h]--; //decrease the amount of enemy left
            }
            else
            {
              digitalWrite(led, LOW); //led off if not shoot/ playbutton off
            }
          }
        }
      }
    }

    lcd.clear();
    lcd.print("Game Over"); //After 10 rounds finish, the game is over.
    delay(5000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Button "); //The game ask for user to press start button gain if want to try again
    lcd.setCursor(0, 1);
    lcd.print("To Try Again");
    delay(250);
    if (digitalRead(startbutton));
    startGame = 1;
  }
}

//display intro messages
void intro()
{
  while (test2)
  {
    lcd.clear();
    lcd.print("Welcome To");
    lcd.setCursor(0, 1);
    lcd.print("Shooting Games");
    delay(3000);
    test2 = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button"); //press button to start the game
  lcd.setCursor(0, 1);
  lcd.print("To Start");
  delay(250);
  startGame = digitalRead(startbutton);
}

//interrupt function: Read, and store angle value && move the servo according to the angle
void Read()
{
  mpuRead();
  mapp = map(yawAngle, 0, 255, 0, 180);
  // Serial.println(mapp);
  myservo.write(mapp);
}
