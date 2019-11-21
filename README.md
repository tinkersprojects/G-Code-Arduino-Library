# G-Code Arduino Library
[https://tinkersprojects.com/](https://tinkersprojects.com/)  
This is a library that alows any machine or robot to be controlled by G-Code

#### Features
- serial or character input
- Customisable 

### What is G-Code?
G-Code is the instructions that 3D Printer and CNC used to create there part. G-Code is a set of instruction commands sent to the controller of the machine to be performed. Position, feed rate, and tool used are some of the items that G-Code can control. The G-Code can either be sent from the computer or saved on an SD card.

### Why make this library?
This library allows any machine or robot to be controlled by G-Code. It makes it quick and easy to set up with CNC and machine software and gives much better control over the communications and commands.

### Why use this?
If your project requires computer control or a set of instruction, a library like this will help simplify this process of making it your self.


## Functions
### SETUP
#### gcode(),<br> gcode(void (*CallBack)()),<br> gcode(int numbercommands, commandscallback *commandArray),<br> gcode(int numbercommands, commandscallback *commandArray, void (*CallBack)());
This Function is used to declare this class so that it can be used in the program. There are 4 different functions, each with variables that can be set. The *callback* is used to link a call back function used after each command is available. *commandArray* is an array of callback that interupt the program to execute the command. *Numbercommands* is the number of items within commandArray.

#### void begin(),<br> void begin(int bitrate)
This Function must be called if the serial interface is wanting to be used. *Bitrate* is the bitrate of the serial port. If this is called, there is no need to *Serial.begin();*, it is apart of the begin function.

### SEND 
#### void comment(String comment)
This Function is to send comments back through the serial. *Comment* would be the comment that would be sent back.

### RECEIVE
#### bool available(),<br> bool available(char inChar)
This function reads the incoming data and returns true then the command is ready to for the program to read an control the machine. *InChar* is the input from a source like an SD card.

#### double GetValue(char commandLetter)
This function is to return the values for a command letter. *CommandLetter* is the command letter that is requested to be returned.

## Example
### Example 1: LED_Control
```c++
#include <gcode.h>

#define LEDpin 13
#define NumberOfCommands 2

void homing();
commandscallback commands[NumberOfCommands] = {{"L1",OnLED},{"L2",OffLED}};
gcode Commands(NumberOfCommands,commands);

void setup()
{
  Commands.begin();
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
```

### Example 2: simplePloter
```c++
#include <gcode.h>

void homing();
commandscallback commands[1] = {{"G28",homing}};
gcode Commands(1,commands);

double X;
double Y;

void setup()
{
  Commands.begin();
}

void loop() 
{
  if(Commands.available())
  {
    double newXValue = X;
    double newYValue = Y;
    
    if(Commands.availableValue('X'))
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))
      newYValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
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

### Example 3: CoreXY
```c++
#include <gcode.h>

#define Speed 100

void homing();
commandscallback commands[1] = {{"G28",homing}};
gcode Commands(1,commands);

double X;
double Y;
double A;
double B;

void setup()
{
  Commands.begin();
}

void loop() 
{
  if(Commands.available())
  {
    double newXValue = X;
    double newYValue = Y;
    
    if(Commands.availableValue('X'))
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))
      newYValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
  }
}

void homing()
{
  // code to home machine
}

void gotoLocation(double NewX,double NewY)
{
  double YCurrent = 0.5*(A + B);
  double XCurrent = 0.5*(A - B);
  double R = sqrt((NewY-YCurrent)*(NewY-YCurrent)+(NewX-XCurrent)*(NewX-XCurrent));
  double t = R/Speed;

  double ANewPosition = NewX+NewY;
  double BNewPosition = NewX-NewY;
  double SpeedA = abs(ANewPosition - A)/t;
  double SpeedB = abs(ANewPosition - B)/t;
  
  X = NewX;
  Y = NewY;
  A = ANewPosition;
  B = BNewPosition;

  // code to run machine to location using:
  //  - ANewPosition (or A) and BNewPosition (or B)
  //  - SpeedA and SpeedB
}
```
