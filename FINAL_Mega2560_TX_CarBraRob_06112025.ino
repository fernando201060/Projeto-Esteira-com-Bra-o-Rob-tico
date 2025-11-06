/*
---- Transmitter Code ----
*/

#include <SPI.h>
#include "RF24.h"

unsigned long SetTime;
int joystick[12];

RF24 radio(7,8);                   
                                      
const uint64_t pipeOut = 0x7878787878LL;
   
void setup(void)
{
  radio.begin();
  radio.setPALevel( RF24_PA_LOW );     //RF24_PA_MIN  / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS );   //RF24_250KBPS / RF24_1MBPS  / RF24_2MBPS
  radio.openWritingPipe(pipeOut);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(9, OUTPUT);

}

void loop(void)
{
  joystick[0] = analogRead(0);  
  joystick[1] = analogRead(1); 
  joystick[2] = analogRead(2);
  joystick[3] = analogRead(3);
  joystick[4] = analogRead(4);
  joystick[5] = analogRead(5);
  joystick[6] = analogRead(6);
  joystick[7] = analogRead(7);
  joystick[8] = digitalRead(2);
  joystick[9] = digitalRead(3);
  joystick[10] = digitalRead(4);
  joystick[11] = digitalRead(5);

  radio.write(joystick, sizeof(joystick) );

  if (millis() - SetTime < 100)
  {
    digitalWrite(9, HIGH);
  }
  else if (millis() - SetTime < 200)
  {
    digitalWrite(9, LOW);
  }
  else
  {
    SetTime = millis();
  }
}
