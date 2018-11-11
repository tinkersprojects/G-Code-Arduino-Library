# G-Code Arduino Library (working progress, no examples yet)
This is a library that alows any machine or robot to be controlled by G-Code

#### Features

### What is G-Code?

### Why make this library?

### How it works?

### Why use this?

## Functions
### SETUP
#### RGB_LED(byte pinR,byte pinG,byte pinB)

### SET 

### GET

### COMMANDS 

## Example
### Example 1: Fade

```c++
#include <RGB_LED.h>

RGB_LED LED(9,10,11);

void setup() 
{
  LED.setFunction(Fade);
}

void loop() 
{
   LED.run();
}
```

### Example 2: Two LEDs

```c++
#include <RGB_LED.h>

RGB_LED LED1(9,10,11);
RGB_LED LED2(3,4,5);

void setup() 
{
  LED1.setFunction(Fade);
  LED2.setFunction(Step);
}

void loop() 
{
   LED1.run();
   LED2.run();
}
```

### Example 3: Set Speed

```c++
#include <RGB_LED.h>

#define upButtonPin 4
#define downButtonPin 5

unsigned int speed = 1000;

RGB_LED LED(9,10,11);

void setup() 
{
  pinMode(upButtonPin,INPUT);
  pinMode(downButtonPin,INPUT);
  LED.setFunction(Fade);
}

void loop() 
{
   LED.run();

   if(digitalRead(downButtonPin)==HIGH && speed<100)
   {
      speed--;
      LED.setSpeed(speed);
      LED.delay(10);
   }
   if(digitalRead(upButtonPin)==HIGH && speed>20000)
   {
      speed++;
      LED.setSpeed(speed);
      LED.delay(10);
   }
}
```
