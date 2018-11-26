# G-Code Arduino Library (trying to debug and document)
This library is mostly woking but still working through some examples and debugging parts
This is a library that alows any machine or robot to be controlled by G-Code

#### Features
- serial or character input
- Customisable 

### What is G-Code?
G-Code is the the instructions that 3D Printer and CNC used to creat there part. G-Code is a set of instruction commands sent to the machines controller to to be performed. Posistion, feed rate and tool used are some of the items that G-Code can control. The G-Code can either be sent from the computer or saved on an SD card.

### Why make this library?
This library allows any machine or robot to be controlled by G-Code. It make it quick and easy to setup with CNC and machine software and gives much better control over the communications and commands. 

### How it works?

### Why use this?
If your project requires computer control or a set of instruction, a library like this will help simplify this proccess of making it your self. 

## Functions
### SETUP
#### gcode**(),<br> gcode(void (*CallBack)()),<br> gcode(int numbercommands, commandscallback *commandArray),<br> gcode(int numbercommands, commandscallback *commandArray, void (*CallBack)());
wer
#### void begin(),<br> void begin(int bitrate)

### SEND 
#### void comment(String comment)
#### void command(char number, double values)

### RECEIVE
#### bool available()
#### bool available(char inChar)
#### double GetValue(char commandLetter)
#### void clearBuffer()

## Example
### Example 1: CoreXY
```c++
#include <gcode.h>

#define XMultiplier 1
#define YMultiplier 1

#define Speed 200

#define XHomeLimitPin 2
#define YHomeLimitPin 3
#define AStepPin 4
#define BStepPin 5
#define ADirPin 6
#define BDirPin 7

double X;
double Y;
long A;
long B;
long ACurrent;
long BCurrent;
unsigned long ALastRun;
unsigned long BLastRun;

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

void setup()
{
  pinMode(XHomeLimitPin,INPUT);
  pinMode(YHomeLimitPin,INPUT);
  pinMode(XStepPin,OUTPUT);
  pinMode(YStepPin,OUTPUT);
  pinMode(XDirPin,OUTPUT);
  pinMode(YDirPin,OUTPUT);

  Commands.begin();
  //homing();
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
  while(digitalRead(XHomeLimitPin)==LOW && digitalRead(YHomeLimitPin)==LOW)
  {
    XCurrent = 0;
    YCurrent = 0;
    X = -1;
    Y = -1;
    runStepperMotors();
  }
  XCurrent = 0;
  YCurrent = 0;
  X = 0;
  Y = 0;
}

void gotoLocation(double x,double y)
{
  X = x*XMultiplier;
  Y = y*YMultiplier;
  A = X+Y;
  B = X-Y;
  while(ACurrent != A || BCurrent != B )
  {
    runStepperMotors();
  }
}

void runStepperMotors()
{
  double angle = atan2(YCurrent-Y,XCurrent-X);
  double XSpeed = cos(angle)*XMultiplier/(Speed*1000);
  double YSpeed= sin(angle)*YMultiplier/(Speed*1000);

  double ASpeed = XSpeed+YSpeed;
  double BSpeed = XSpeed-YSpeed;

  if(ACurrent!=A && ALastRun+ASpeed<millis())
  {
    XLastRun = millis();
    if(XCurrent<X)
    {
      digitalWrite(ADirPin,HIGH);
      ACurrent++;
    }
    else
    {
      digitalWrite(ADirPin,LOW);
      ACurrent--;
    }

    digitalWrite(AStepPin,HIGH);
    digitalWrite(AStepPin,LOW);
  }

  if(BCurrent!=B && BLastRun+BSpeed<millis())
  {
    BLastRun = millis();
    if(BCurrent<B)
    {
      digitalWrite(BDirPin,HIGH);
      BCurrent++;
    }
    else
    {
      digitalWrite(BDirPin,LOW);
      BCurrent--;
    }

    digitalWrite(BStepPin,HIGH);
    digitalWrite(BStepPin,LOW);
  }
}
```

### Example 2: RobotWithSD

```c++
#include <gcode.h>

#define XMultiplier 1
#define YMultiplier 1

#define Speed 200

#define XHomeLimitPin 2
#define YHomeLimitPin 3
#define XStepPin 4
#define YStepPin 5
#define XDirPin 6
#define YDirPin 7

long X;
long Y;
long XCurrent;
long YCurrent;
unsigned long XLastRun;
unsigned long YLastRun;

double xSpeed;
double ySpeed;

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

void setup()
{
  pinMode(XHomeLimitPin,INPUT);
  pinMode(YHomeLimitPin,INPUT);
  pinMode(XStepPin,OUTPUT);
  pinMode(YStepPin,OUTPUT);
  pinMode(XDirPin,OUTPUT);
  pinMode(YDirPin,OUTPUT);

  Commands.begin();
  //homing();
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
  while(digitalRead(XHomeLimitPin)==LOW && digitalRead(YHomeLimitPin)==LOW)
  {
    XCurrent = 0;
    YCurrent = 0;
    X = -1;
    Y = -1;
    runStepperMotors();
  }
  XCurrent = 0;
  YCurrent = 0;
  X = 0;
  Y = 0;
}

void gotoLocation(double x,double y)
{
  X = x*XMultiplier;
  Y = y*YMultiplier;
  while(XCurrent != X || YCurrent != Y )
  {
    runStepperMotors();
  }
}

void runStepperMotors()
{
  double angle = atan2(YCurrent-Y,XCurrent-X);
  double XSpeed = cos(angle)*XMultiplier/(Speed*1000);
  double YSpeed= sin(angle)*YMultiplier/(Speed*1000);

  if(XCurrent!=X && XLastRun+XSpeed<millis())
  {
    XLastRun = millis();
    if(XCurrent<X)
    {
      digitalWrite(XDirPin,HIGH);
      XCurrent++;
    }
    else
    {
      digitalWrite(XDirPin,LOW);
      XCurrent--;
    }

    digitalWrite(XStepPin,HIGH);
    digitalWrite(XStepPin,LOW);
  }

  if(YCurrent!=Y && YLastRun+YSpeed<millis())
  {
    YLastRun = millis();
    if(YCurrent<Y)
    {
      digitalWrite(YDirPin,HIGH);
      YCurrent++;
    }
    else
    {
      digitalWrite(YDirPin,LOW);
      YCurrent--;
    }

    digitalWrite(YStepPin,HIGH);
    digitalWrite(YStepPin,LOW);
  }
}

```

### Example 3: simplePloter

```c++
#include <gcode.h>

#define XMultiplier 1
#define YMultiplier 1

#define Speed 200

#define XHomeLimitPin 2
#define YHomeLimitPin 3
#define XStepPin 4
#define YStepPin 5
#define XDirPin 6
#define YDirPin 7

long X;
long Y;
long XCurrent;
long YCurrent;
unsigned long XLastRun;
unsigned long YLastRun;

double xSpeed;
double ySpeed;

void homing();
commandscallback commands[1] = {{"g28",homing}};
gcode Commands(1,commands);

void setup()
{
  pinMode(XHomeLimitPin,INPUT);
  pinMode(YHomeLimitPin,INPUT);
  pinMode(XStepPin,OUTPUT);
  pinMode(YStepPin,OUTPUT);
  pinMode(XDirPin,OUTPUT);
  pinMode(YDirPin,OUTPUT);

  Commands.begin();
  //homing();
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
  while(digitalRead(XHomeLimitPin)==LOW && digitalRead(YHomeLimitPin)==LOW)
  {
    XCurrent = 0;
    YCurrent = 0;
    X = -1;
    Y = -1;
    runStepperMotors();
  }
  XCurrent = 0;
  YCurrent = 0;
  X = 0;
  Y = 0;
}

void gotoLocation(double x,double y)
{
  X = x*XMultiplier;
  Y = y*YMultiplier;
  while(XCurrent != X || YCurrent != Y )
  {
    runStepperMotors();
  }
}

void runStepperMotors()
{
  double angle = atan2(YCurrent-Y,XCurrent-X);
  double XSpeed = cos(angle)*XMultiplier/(Speed*1000);
  double YSpeed= sin(angle)*YMultiplier/(Speed*1000);

  if(XCurrent!=X && XLastRun+XSpeed<millis())
  {
    XLastRun = millis();
    if(XCurrent<X)
    {
      digitalWrite(XDirPin,HIGH);
      XCurrent++;
    }
    else
    {
      digitalWrite(XDirPin,LOW);
      XCurrent--;
    }

    digitalWrite(XStepPin,HIGH);
    digitalWrite(XStepPin,LOW);
  }

  if(YCurrent!=Y && YLastRun+YSpeed<millis())
  {
    YLastRun = millis();
    if(YCurrent<Y)
    {
      digitalWrite(YDirPin,HIGH);
      YCurrent++;
    }
    else
    {
      digitalWrite(YDirPin,LOW);
      YCurrent--;
    }

    digitalWrite(YStepPin,HIGH);
    digitalWrite(YStepPin,LOW);
  }
}

```
