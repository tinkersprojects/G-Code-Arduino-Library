# RGB_LED Library
RGB LEDs are used everywhere, in many different products and devices. This Arduino library is to the control RGB LED's colour and fading between colours. Almost every setting can be controlled though this library to control the RGB LEDs.
The library contains preset colours and fuctions to make it easier to construct your RGB LED project.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=i7A1KCqNQHQ
" target="_blank"><img src="http://img.youtube.com/vi/i7A1KCqNQHQ/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a> <a href="http://www.youtube.com/watch?feature=player_embedded&v=WD0Sz2w0R2Y
" target="_blank"><img src="http://img.youtube.com/vi/WD0Sz2w0R2Y/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a> <a href="http://www.youtube.com/watch?feature=player_embedded&v=xD3Qw-6c8vk
" target="_blank"><img src="http://img.youtube.com/vi/xD3Qw-6c8vk/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

## circuit
Any PWM pins can be used for and LED/LED color. Below is and example for pin 9 = red, pin 10 = green and pin 11 = blue. 

```c++
RGB_LED LED(9,10,11);
```

![circuit](https://github.com/tinkersprojects/RGB_LED/blob/master/images/circuit.png "circuit")


## Functions
### SETUP
#### RGB_LED(byte pinR,byte pinG,byte pinB)
This is the setup for the class, this is where the pins are declared for the RGB LED. *pinR*, *pinG* and *pinB* is where the PWM pin numbers are placed.
### SET 
#### void set(byte Rvalue,byte Gvalue,byte Bvalue)
This function sets a RGB colour. It will stop a fade to be the set color. *Rvalue*, *Gvalue* and *Bvalue* are used to set the RGB colour. These RGB Byte variables are the values between 0 and 255. 0 is the LED completely off, 255 is the LED Completely on and all values between is a PWM percent.
#### void setSpeed(unsigned long speedValue)
This Functions sets the speed of fades and the speed of colour functions. The *speedValue* is in milliseconds and is used from the start to the finish of the fade.
#### void setPercentFade(float FadeValue)
This function set the where the fade is. The *FadeValue* is a between 0 and 1. If the *FadeValue* is set to be 0.5 at 1000 speed the fade would continue from 50%. 
#### void fadeTo(byte Rvalue,byte Gvalue,byte Bvalue,unsigned long speedValue)
This function is used to fade from the current set colour to a RGB colour at a speed. *Rvalue*, *Gvalue* and *Bvalue* are used to set the RGB colour and *speedValue* is used to set the fade speed. These *Rvalue*, *Gvalue* and *Bvalue* Byte variables are the values between 0 and 255. 0 is the LED completely off, 255 is the LED Completely on and all values between is a PWM percent. The *speedValue* is in milliseconds and is used from the start to the finish of the fade.
#### void setFunction(byte functionValue)
This function is used to select a LED colour function. All the LED's colour functions are listed below under *Colour Functions*
#### void setRandom()
This will make the LED fade to a random colour with a random fade speed.
#### void setColour(byte colour)
This will set the LED to a selected colour. The *colour* can be chosen from the colours list below.
#### void fadeToColour(byte colour,unsigned long speedValue)
This will make the LED fade to a selected colour with a selected fade speed. The *colour* can be chosen from the colours list below. The *speedValue* is in milliseconds and is used from the start to the finish of the fade. 
### GET
#### unsigned long getSpeed()
This will return the current set speed in milliseconds.
#### float getPercentFade()
This will return the current fade percent of completion.
#### byte getFunction()
This will return the current set function.
#### byte getCurrentRValue()
This will return the current Red value.
#### byte getCurrentGValue()
This will return the current Green value.
#### byte getCurrentBValue()
This will return the current Blue value.
#### int getFunctionCount()
This will return the current functions step count.
### CHECKING 
#### boolean hasFinished()
This checks if the fade as finished and returns *true* when finished
### COMMANDS 
#### void run()
This function is required to run as much as possible. This function runs the calculates and the controls the PWM for the LED.
#### void stop()
This will stop all current fading and freeze the colour.
#### void delay(unsigned long delayValue)
This function is used in replacement of *Delay()*. This delay will continue to process the *run()* function.

## Colours
- Black
- White
- Red
- Green
- Blue
- Yellow
- Purple
- Aqua

## Colour Functions
- **Random:** this randomly fades betweens random colours at random speeds.
- **Solid:** this stays at a set colour.
- **Fade:** this fades betweens Red, Green and blue colours at a set speed.
- **FadeRandom:** this fades betweens random colours at a set speeds.
- **Step1:** this steps betweens Red, Green and blue colours at a set speed.
- **Step2:** this steps betweens all colours at a set speed.
- **StepRandom:** this steps betweens random colours at a set speeds.

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
