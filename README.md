# G-Code Arduino Library
This is a library that alows any machine or robot to be controlled by G-Code

#### Features
- serial or character input
- Customisable 

### What is G-Code?
G-Code is the the instructions that 3D Printer and CNC used to creat there part. G-Code is a set of instruction commands sent to the machines controller to to be performed. Posistion, feed rate and tool used are some of the items that G-Code can control. The G-Code can either be sent from the computer or saved on an SD card.

### Why make this library?
This library allows any machine or robot to be controlled by G-Code. It make it quick and easy to setup with CNC and machine software and gives much better control over the communications and commands. 

### Why use this?
If your project requires computer control or a set of instruction, a library like this will help simplify this proccess of making it your self. 

## Functions
### SETUP
#### gcode(),<br> gcode(void (*CallBack)()),<br> gcode(int numbercommands, commandscallback *commandArray),<br> gcode(int numbercommands, commandscallback *commandArray, void (*CallBack)());
This Function is used to declare this class so that it can be used in the program. There is 4 different functions, each with  variables that can be set. *CallBack* is used to link a call back function used after each command is available. *commandArray* is an array of callback that interupt the program to exucute the command. *Numbercommands* is the number of items with in commandArray.

#### void begin(),<br> void begin(int bitrate)
This Function must be called if the serial interface is wanting to be used. *Bitrate* is the bitrate of the serial port. If this is called, there is no need to *Serial.begin();*, it is appart of the begin function.

### SEND 
#### void comment(String comment)
This Function is to send comments back through the serial. *Comment* would be the comment that would be sent back.

### RECEIVE
#### bool available(),<br> bool available(char inChar)
This function reads the incoming data and returns true then the command is ready to for the program to read an control the machine. *InChar* is the input from a source like an SD card.

#### double GetValue(char commandLetter)
This function is to return the values for a command letter. *CommandLetter* is the command letter that is requested to be returned.

## Example
### Example 1: simplePloter

```c++
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

void gotoLocation(double x,double y)
{
  // code to run machine to location
}
```

### Example 2: CoreXY/HBot
```c++
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
  // Cal to come

  double ASpeed = XSpeed+YSpeed;
  double BSpeed = XSpeed-YSpeed;
  double ANewPosition = X+Y;
  double BNewPosition = X-Y;


  // code to run machine to location using:
  //  - ANewPosition and BNewPosition
  //  - ASpeed and BSpeed
}
```

### Example 3: RobotWithSD

```c++
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
```

