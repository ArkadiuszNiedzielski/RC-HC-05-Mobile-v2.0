#include <Arduino.h>
#include <SoftwareSerial.h>
#define LEFT_PWM 5
#define RIGHT_PWM 6
#define LEFT_DIRECTION 4      // It means LEFT ENGINE and RIGHT ENGINE (2 engines for driving forward and backward)
#define RIGHT_DIRECTION 9
#define LEFT_ROTATION 12      // Tower rotation left or right (1 engine)
#define RIGHT_ROTATION 11
#define PWM_MAX 165
#define BUZZ 10

SoftwareSerial bluetooth(7, 8); // RX, TX respetively

void exeCmd();
void leftEngine(int SPEED);
void rightEngine(int SPEED);
void stopEngines();

char cmd[100];    //  Table to reading commands from mobile 
byte cmdIndex=0;  // Index of table
int value=0;       
unsigned long currentTime=0,DifferenceTime = 0; // research
char c=0;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(LEFT_DIRECTION, OUTPUT);
  pinMode(RIGHT_DIRECTION, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(BUZZ, OUTPUT);
}

void loop()
{

  if (bluetooth.available() > 0)        //  if bluetooth is connect
  {

    c = (char)bluetooth.read();         // read data and save in variable
    if (c == '\n')                      
    {

      DifferenceTime=millis()-currentTime; //research
      currentTime = millis(); // research

      Serial.println(DifferenceTime); //research

      cmd[cmdIndex] = 0;                
      exeCmd();
      cmdIndex = 0;
    }
    else
    {
      cmd[cmdIndex] = c;
      if (cmdIndex < 99)
        cmdIndex++;
    }
  }
}

void exeCmd()
{

  if (cmd[0] == 's')
  {
    value = atof(cmd + 2);
    leftEngine(value);
  }

  if (cmd[0] == 'S')
  {
    value = atof(cmd + 2);
    rightEngine(value);
  }

  if (cmd[0] == 'L')
    digitalWrite(LEFT_ROTATION, HIGH);  

  if (cmd[0] == 'l')
    digitalWrite(LEFT_ROTATION, LOW);
  
  if (cmd[0] == 'P')
    digitalWrite(RIGHT_ROTATION, HIGH);
  
  if (cmd[0] == 'p')
    digitalWrite(RIGHT_ROTATION, LOW);
  
  if (digitalRead(LEFT_ROTATION) == HIGH && digitalRead(RIGHT_ROTATION) == HIGH)  //  short-circuit protection
  {
    digitalWrite(LEFT_ROTATION, LOW);
    digitalWrite(RIGHT_ROTATION, LOW);
  }

  if (cmd[0] == 'H')
    digitalWrite(BUZZ, HIGH);
  

  if (cmd[0] == 'h')
    digitalWrite(BUZZ, LOW);  
}

void leftEngine(int SPEED)
{
  if (SPEED > 0)
  {
    SPEED = map(SPEED, 0, 100, 0, PWM_MAX);
    digitalWrite(LEFT_DIRECTION, LOW);
    analogWrite(LEFT_PWM, SPEED);
  }
  else
  {
    SPEED = abs(SPEED);
    SPEED = map(SPEED, 0, 100, 0, PWM_MAX);
    digitalWrite(LEFT_DIRECTION, HIGH);
    analogWrite(LEFT_PWM, SPEED);
  }
}
void rightEngine(int SPEED)
{
  if (SPEED > 0)
  {
    SPEED = map(SPEED, 0, 100, 0, PWM_MAX);
    digitalWrite(RIGHT_DIRECTION, LOW);
    analogWrite(RIGHT_PWM, SPEED);
  }
  else
  {
    SPEED = abs(SPEED);
    SPEED = map(SPEED, 0, 100, 0, PWM_MAX);
    digitalWrite(RIGHT_DIRECTION, HIGH);
    analogWrite(RIGHT_PWM, SPEED);
  }
}
void stopEngines()
{
  analogWrite(LEFT_PWM, LOW);
  analogWrite(RIGHT_PWM, LOW);
}


/*
Arkadiusz Niedzielski 42237

Engineering project

Topic: "Implementation project and analysis of a simple robot control system using a wireless network."

All lines marked as "research" are not required to run robot. They are used for latency analysis.  
*/

