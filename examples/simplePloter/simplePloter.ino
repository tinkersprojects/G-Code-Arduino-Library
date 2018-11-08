#include <gcode.h>

void homing();
commandscallback wer[2] = {{'g',28,1,homing},{'g',22,1,homing}};
gcode Commands(wer);

void setup()
{
  Commands.begin();
}

void loop() 
{
  if(Commands.available())
  {
    gotoLocation(Commands.GetValue('X'),Commands.GetValue('Y'),Commands.GetValue('Z'));
  }
}

void homing()
{
  gotoLocation(0,0,0);
}

void gotoLocation(double x,double y,double z)
{
Serial.print(x);
Serial.print(",");
Serial.print(y);
Serial.print(",");
Serial.print(z);
Serial.println("");
}