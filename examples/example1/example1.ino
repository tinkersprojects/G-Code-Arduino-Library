#include <RGB_LED.h>

RGB_LED LED(9,10,11);

void setup() 
{
  LED.setFunction(Fade);
}

void loop() 
{
   LED.run();
}