#include <gcode.h>
#include <DeltaKinematics.h> // Requires Delta Kinematics library from  https://github.com/tinkersprojects/Delta-Kinematics-Library

gcode Commands;
DeltaKinematics DK(70,300,139,112);

void setup()
{
  Commands.begin("OK");  // ok, rs or !!
}

void loop() 
{
  if(Commands.available())
  { 
    if(Commands.availableValue('X'))
    {
      DK.x  = Commands.GetValue('X');
    }

    if(Commands.availableValue('Y'))
    {
      DK.y = Commands.GetValue('Y');
    }

    if(Commands.availableValue('Z'))
    {
      DK.z = Commands.GetValue('Z');
    }
      
    DK.inverse();

    //GOTO Position XYZ
    // Move robot motors to DK.a, DK.b and DK.c CODE
      
    Commands.comment('X',DK.x);
    Commands.comment('Y',DK.y);
    Commands.comment('Z',DK.z);
    Commands.comment('a',DK.a);
    Commands.comment('b',DK.b);
    Commands.comment('c',DK.c);

  }
}
