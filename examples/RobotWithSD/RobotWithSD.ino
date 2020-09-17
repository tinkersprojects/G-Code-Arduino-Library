#include <gcode.h>
#include <SPI.h>
#include <SD.h>

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

double X;
double Y;

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
        double newXValue = X;
        double newYValue = Y;
        
        if(Commands.availableValue('X'))
          newXValue = Commands.GetValue('X');
        if(Commands.availableValue('Y'))
          newXValue = Commands.GetValue('Y');

        gotoLocation(newXValue,newYValue);
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
