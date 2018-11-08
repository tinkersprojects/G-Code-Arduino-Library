#include <gcode.h>

void homing();
void absoluteMode();
void relativeMode();
gcode code(9600);

void setup()
{
  code.setCommand('G', 28, homing);
  code.setCommand('G', 90, absoluteMode);
  code.setCommand('G', 91, relativeMode);
}

void loop() 
{
  if(code.available())
  {
    
  }
}

void homing()
{

}

void absoluteMode()
{

}

void relativeMode()
{

}