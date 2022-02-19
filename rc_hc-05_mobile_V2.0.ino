
#include <SoftwareSerial.h>
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
#define BUZZ 10

SoftwareSerial bluetooth(7, 8);     // TX, RX respetively


void setup() 
{
  bluetooth.begin(9600);  
  
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);  
  pinMode(BUZZ, OUTPUT); 
  
  
}


char cmd[100];
byte cmdIndex;
boolean buzz;
int val,val2;
 
void exeCmd() {

  
  if (cmd[0] == 's') {
    val = atof(cmd + 2);
    leftMotor(-val);    
  }

    if (cmd[0] == 'S') {
    val2 = atof(cmd + 2);  
    rightMotor(val2);     
      }

      
    if (cmd[0] == 'L') {
      digitalWrite(12, HIGH);
      }

     if (cmd[0] == 'l') {
      digitalWrite(12, LOW);
      }

    if (cmd[0] == 'P') {
      digitalWrite(13, HIGH);
      }

    if (cmd[0] == 'p') {
      digitalWrite(13, LOW);
      }

    if (digitalRead(12)==HIGH && digitalRead(13)==HIGH) {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      
      }
      
    if (cmd[0] == 'H') {
      digitalWrite(10, HIGH);
      }

    if (cmd[0] == 'h') {
      digitalWrite(10, LOW);
      }
        
}
 
void loop() 
{
   
   if (bluetooth.available() > 0  ) 
  {
    
    char c = (char)bluetooth.read();
    if (c == '\n') {
      cmd[cmdIndex] = 0;
      exeCmd();
      cmdIndex = 0;
    } else {
      cmd[cmdIndex] = c;
      if (cmdIndex < 99) cmdIndex++;
    }
  }
   
   
   
 
}



void leftMotor(int V) {
  if (V > 0) { //jeśli prędkość jest większa od 0 (dodatnia)
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0); //kierunek do przodu
    analogWrite(L_PWM, V); //ustawienie prędkości
  } else {
    V = abs(V); //funkcja abs() zwróci wartość V  bez znaku
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1); //kierunek: do tyłu
    analogWrite(L_PWM, V); //ustawienie prędkości
  }
}
void rightMotor(int V) {
  if (V > 0) { //jeśli predkość jest większa od 0 (dodatnia)
    V = map(V, 0, 100, 0, PWM_MAX); //130 bo prawy silnik słabszy
    digitalWrite(R_DIR, 0); //kierunek: do przodu
    analogWrite(R_PWM, V); //ustawienie predkości
  } else {
    V = abs(V); //funkcja abs() zwróci wartość V  bez znaku
    V = map(V, 0, 100, 0, PWM_MAX); //130 bo prawy silnik słabszy
    digitalWrite(R_DIR, 1); //kierunek: do tyłu
    analogWrite(R_PWM, V); //ustawienie prędkości
  }
}
void stopMotors() {
  analogWrite(L_PWM, 0); //wyłączenie lewego silnika
  analogWrite(R_PWM, 0); //wyłączenie prawego silnika
}
