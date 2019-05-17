#include <gcode.h>
#include <SPI.h>
#include <SD.h>

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

void setup()
{
  Commands.begin();

  if (!SD.begin(chipSelect)) 
  {
    Commands.comment("Card failed");
    while (1);
  }

  File dataFile = SD.open("test.gcode");


  if (dataFile) 
  {
    while (dataFile.available()) 
    {
      if(Commands.available(dataFile.read()))
      {
        gotoLocation(Commands.GetValue('X'),Commands.GetValue('Y'));
      }
    }
    dataFile.close();
  }
  else
  {
    Commands.comment("error opening file");
  }
}

void loop() 
{
  
}

void homing()
{
  // code to home machine
}

void gotoLocation(double x,double y)
{
  // code to run machine to location
}
