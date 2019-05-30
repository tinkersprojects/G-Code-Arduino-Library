#include <gcode.h>

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

double X;
double Y;

void setup()
{
  Commands.begin();
}

void loop() 
{
  if(Commands.available())
  {
    double newXValue = X;
    double newYValue = Y;
    
    if(Commands.availableValue('X'))
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))
      newXValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
  }
}

void homing()
{
  // code to home machine
}

void gotoLocation(double x,double y)
{
  // code to run machine to location
}
