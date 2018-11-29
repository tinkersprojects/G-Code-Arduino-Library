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
  double R = sqrt((Y-YCurrent)*(Y-YCurrent)+(X-XCurrent)*(X-XCurrent));
  double t = R/Speed;

  double Speeda = abs(a - stepperA.currentPosition())/t;
  double Speedb = abs(b - stepperB.currentPosition())/t;
  double ANewPosition = X+Y;
  double BNewPosition = X-Y;


  // code to run machine to location using:
  //  - ANewPosition and BNewPosition
  //  - ASpeed and BSpeed
}
