# G-Code Arduino Library (not working and no examples yet)
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
#### gcode()
#### gcode(void (*CallBack)())
#### gcode(commandscallback *commandscallbacks_temp)
#### void begin()
#### void begin(int bitrate)

### SEND 
#### void comment(String comment)
#### void command(char number, double values)

### RECEIVE
#### bool available()
#### bool available(char inChar)
#### double GetValue(char commandLetter)
#### void clearBuffer()

## Example
### Example 1: Fade
```c++
#include <gcode.h>

```

### Example 2: Two LEDs

```c++
#include <gcode.h>

```

### Example 3: Set Speed

```c++
#include <gcode.h>

```
