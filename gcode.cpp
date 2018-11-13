/**********************************************************************************************
 * Arduino LED RGB Library - Version 1.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/
#define version 1.0

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "gcode.h"

/******************* SETUP *******************/

gcode::gcode()
{
}

gcode::gcode(commandscallback *commandscallbacks_temp)
{
  commandscallbacks = commandscallbacks_temp;
}

gcode::gcode(void (*CallBack)())
{
  runCallback = CallBack;
}

void gcode::begin()
{
  Serial.begin(9600);
  Serial.println("v" +String(version)+" Simple G code");
}

void gcode::begin(int bitrate)
{
  Serial.begin(bitrate);
  Serial.println("v" +String(version)+" Simple G code");
}


/******************* receive *******************/

void gcode::clearBuffer()
{
    commandLetter = 0;
    commandBuffer = "";
    commandValue = 0;
}

bool gcode::available()
{
    while (Serial.available()) 
    {
        char inChar = (char)Serial.read();
        if(gcode::available(inChar))
        {
            return true;
        }
    }
    return false;
}

bool gcode::available(char inChar)
{
    if(inChar == ' ' || inChar == '\n')
    {
        if(commandBuffer != "")
        {
            if(commandLetter == 0)
            {
                commandsList[0] = commandBuffer.toDouble();
            }
            else if(commandLetter >= 'A' && commandLetter <= 'Z')
            {
                commandsList[commandLetter - 'A' + 1] = commandBuffer.toDouble();
            }

            // run if command matches

            for(int i = 0; i < 2 /*sizeof(commandscallbacks)*/; i++)
            {
                commandscallback commandscallbackstest = commandscallbacks[i];

                if(commandscallbackstest.value == String(commandLetter)+String(commandBuffer) || commandscallbackstest.value == String(commandLetter-('a'-'A'))+String(commandBuffer))
                {
                    commandscallbackstest.Callback();
                }
            }
        }
        gcode::clearBuffer();
    }

    if(inChar == '\n')
    {
        // run
        restIsComment = false;
        if(runCallback != NULL)
            runCallback();
        return true;
    }

    if(inChar == ';' || restIsComment)
    {
        restIsComment = true;
        return false;
    }

    if(inChar >= 'a' && inChar <= 'z')
    {
        inChar = inChar - ('a'-'A');
    }

    if(inChar >= 'A' && inChar <= 'Z')
    {
        gcode::clearBuffer();
        commandLetter = inChar;
        return false;
    }
    
    if((inChar >= '0' && inChar <= '9') || inChar == '.' || inChar == '-')
    {
        commandBuffer = commandBuffer + String(inChar);
        return false;
    }
    return false;
}

void gcode::comment(String comment)
{
  Serial.println(";" +String(comment));
}

void gcode::command(char number, double values)
{
  Serial.println(String(number)+String(values));
}

double gcode::GetValue(char Letter)
{
    if(Letter >= 'a' && Letter <= 'z')
    {
        Letter = Letter - ('a'-'A');
    }           
    
    if(Letter == ' ')
    {
        return commandsList[0];
    }
    else if(Letter >= 'A' && Letter <= 'Z')
    {
        return commandsList[Letter - 'A' + 1];
    }
    return 0;
}