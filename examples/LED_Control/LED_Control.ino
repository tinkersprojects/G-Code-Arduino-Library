#include <gcode.h>

#define LEDpin 13
#define NumberOfCommands 2

void homing();
commandscallback commands[NumberOfCommands] = {{"L1",OnLED},{"L2",OffLED}};
gcode Commands(NumberOfCommands,commands);

void setup()
{
  Commands.begin("ok"); //responce => ok, rs or !!
  pinMode(LEDpin, OUTPUT);
}

void loop() 
{
  Commands.available();
}

void OnLED()
{
  digitalWrite(LEDpin, HIGH);
}

void OffLED()
{
  digitalWrite(LEDpin, LOW);
}
