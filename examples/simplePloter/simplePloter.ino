#include <gcode.h>

void homing();
void moviment();
/*
G28 - HOMING
G29 - SET COORDINATES -> G29 X{n} Y{n}
*/
#define NUMCOMMANDS 2
commandscallback commands[NUMCOMMANDS] = {{"G28",homing}, {"G29", moviment}}; 
gcode Commands(NUMCOMMANDS,commands);

double X;
double Y;

void setup()
{
  Commands.begin();
}

void loop() 
{
  Commands.available()

}

void homing()
{
  // code to home machine
}

void gotoLocation(double x,double y)
{
  // code to run machine to location
}
// added paramenter x and y in function MOVIMENT > SET GOTO LOCATION;
void moviment(){ 
    double newXValue = X;
    double newYValue = Y;
    if(Commands.availableValue('X')) // ADDED parameter X in G29
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))// ADDED parameter Y in G29
      newYValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
}
