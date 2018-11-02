#include <RGB_LED.h>

#define upButtonPin 4
#define downButtonPin 5

unsigned int speed = 1000;

RGB_LED LED(9,10,11);

void setup() 
{
  pinMode(upButtonPin,INPUT);
  pinMode(downButtonPin,INPUT);
  LED.setFunction(Fade);
}

void loop() 
{
   LED.run();

   if(digitalRead(downButtonPin)==HIGH && speed<100)
   {
      speed--;
      LED.setSpeed(speed);
      LED.delay(10);
   }
   if(digitalRead(upButtonPin)==HIGH && speed>20000)
   {
      speed++;
      LED.setSpeed(speed);
      LED.delay(10);
   }
}