#include <gcode.h>

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

void setup()
{
  Commands.begin();
}

void loop() 
{
  if(Commands.available())
  {
    gotoLocation(Commands.GetValue('X'),Commands.GetValue('Y'));
  }
}

void homing()
{
  // code to home machine
}

void gotoLocation(double X,double Y)
{
  double YCurrent = 0.5*(stepperA.currentPosition() + stepperB.currentPosition());
  double XCurrent = 0.5*(stepperA.currentPosition() - stepperB.currentPosition());
  float angle = atan2(Y-YCurrent,X-XCurrent);
  double angle1 = cos(angle);
  double angle2 = sin(angle);
  double XSpeed = angle1/(Speed);
  double YSpeed = angle2/(Speed);


  double ASpeed = XSpeed+YSpeed;
  double BSpeed = XSpeed-YSpeed;
  double ANewPosition = X+Y;
  double BNewPosition = X-Y;


  // code to run machine to location using:
  //  - ANewPosition and BNewPosition
  //  - ASpeed and BSpeed
}