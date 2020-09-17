#include <gcode.h>

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

double X;
double Y;

void FinishedCommandLine()
{
  Commands.comment("!!"); // ok, rs or !!
  Commands.comment('X',X);
  Commands.comment('Y',Y);
}

void setup()
{
  Commands.begin(FinishedCommandLine);
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
      newYValue = Commands.GetValue('Y');

    X = newXValue;
    Y = newYValue;
    
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