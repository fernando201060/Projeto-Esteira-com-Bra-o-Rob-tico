/*
---- Receiver Code ----
*/

#include <Servo.h>
#include <SPI.h>
#include "RF24.h"  
#define enA 5
#define enB 6
#define in1 3
#define in2 4
#define in3 9
#define in4 10

int motorSpeedA = 0;
int motorSpeedB = 0;

int positionA = 90;
int positionB = 90;
int positionC = 90;
int positionD = 90;
Servo myServoA;
Servo myServoB;
Servo myServoC;
Servo myServoD;

long previousMillis = 0;
long interval = 15;

unsigned long SetTime;

boolean lastButton1 = LOW; 
boolean lastButton2 = LOW;
boolean ledOn1 = false; 
boolean ledOn2 = false;
int buttonState1 = 0;
int buttonState2 = 0;
int joystick[12];

RF24 radio(7,8);

const uint64_t pipeOut = 0x7878787878LL;
   
void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  myServoA.attach(60);
  myServoB.attach(61);
  myServoC.attach(62);
  myServoD.attach(63);
  
  radio.begin();
  radio.setPALevel( RF24_PA_LOW );     //RF24_PA_MIN  / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS );   //RF24_250KBPS / RF24_1MBPS  / RF24_2MBPS
  radio.openReadingPipe(1, pipeOut);
  radio.startListening();       
}

void loop()
{


  
  if(radio.available())
  {       
    bool done = false;      
    while (!done) 
    {
      done = radio.read(joystick, sizeof(joystick));

      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis > interval)
      {
        previousMillis = currentMillis;
        
      if (millis() - SetTime < 30) 
      {
        // digitalWrite(0, HIGH);
        digitalWrite(43, HIGH);
      } 
      else if (millis() - SetTime < 1000)
      {
        // digitalWrite(0, LOW);
        digitalWrite(43, LOW);
      }
      else
      {
        SetTime = millis();
      }

      //WHEEL MOTORS
      int xAxis = joystick[0];
      int yAxis = joystick[1];

      if (yAxis > 550) // Para frente
      {
        
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      else if(yAxis < 470) // Para Trás
      {
        
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH); 
      }
      
      else if (xAxis > 550) // Para a esquerda
      {
         
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      else if(xAxis < 470) // Para a direita
      {
         
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH); 
      }
      else
      {
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW); 
      }

      //SERVOs for Joint 1 and Joint 2

        if(joystick[2] < 412 && positionA < 180)
        {
          positionA+=2;
          myServoA.write(positionA);
        }
        if(joystick[2] > 612 && positionA > 0)
        {
          positionA-=2;
          myServoA.write(positionA);
        }
        if(joystick[3] < 412 && positionB < 180)
        {
          positionB+=2;
          myServoB.write(positionB);
        }
        if(joystick[3] > 612 && positionB > 0)
        {
          positionB-=2;
          myServoB.write(positionB);
        }

      //SERVOs for Joint 3 and Gripper

        if(joystick[4] < 412 && positionC < 180)
        {
          positionC+=2;
          myServoC.write(positionC);
        }
        if(joystick[4] > 612 && positionC > 0)
        {
          positionC-=2;
          myServoC.write(positionC);
        }
        if(joystick[5] < 412 && positionD < 180)
        {
          positionD+=2;
          myServoD.write(positionD);
        }
        if(joystick[5] > 612 && positionD > 0)
        {
          positionD-=2;
          myServoD.write(positionD);
        }

      buttonState1 = joystick[8];
      if (buttonState1 == HIGH && lastButton1 == LOW) 
      {
        ledOn1 = !ledOn1;
        lastButton1 = HIGH;
      }
      else 
      {
        lastButton1 = buttonState1;
      }

      buttonState2 = joystick[9];
      if (buttonState2 == HIGH && lastButton2 == LOW) 
      {
        ledOn2 = !ledOn2;
        lastButton2 = HIGH;
      }
      else 
      {
        lastButton2 = buttonState2;
      }
      // digitalWrite(1, !ledOn1);
      digitalWrite(42, !ledOn1);
      // digitalWrite(43, !ledOn3);
      digitalWrite(2, !ledOn2);
       
    }          
  }
}
}