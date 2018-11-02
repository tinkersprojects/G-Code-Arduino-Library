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
  Serial.begin(115200);
  Serial.println("v" +String(version)+" Simple G code");
}

gcode::gcode(int bitrate)
{
  Serial.begin(bitrate);
  Serial.println("v" +String(version)+" Simple G code");
}

gcode::gcode(int bitrate,void (*CallBack)())
{
  Serial.begin(bitrate);
  Serial.println("v" +String(version)+" Simple G code");
  CallBack = runCallback;
}

gcode::gcode(void (*CallBack)())
{
  Serial.begin(115200);
  Serial.println("v" +String(version)+" Simple G code");
  CallBack = runCallback;
}


/******************* receive *******************/

void gcode::clearBuffer()
{
    commadLetter = 0;
    commandBuffer = "";
    commandValue = 0;
}

void gcode::read()
{
    while (Serial.available()) 
    {
        char inChar = (char)Serial.read();

        if(inChar == ' ' || inChar == '\n')
        {
            if(commandBuffer != "")
            {
                if(commadLetter == 0)
                {
                    commandsList[0] = toDouble(commandBuffer);
                }
                else if(commadLetter >= 'A' && commadLetter <= 'Z')
                {
                    commandsList[commadLetter - 'A' + 1] = toDouble(commandBuffer);
                }

                // run if command matches
                for(int i = 0; i < sizeof(commandscallbacks)/sizeof(commandscallback); i++)
                {
                    if(commandscallbacks[i].includesValue == 1 && commandscallbacks[i].letter == commadLetter)
                    {
                        commandscallbacks[i].Callback();
                    }
                    if(commandscallbacks[i].includesValue == 0 && commandscallbacks[i].letter == commadLetter && commandscallbacks[i].value == toDouble(commandBuffer))
                    {
                        commandscallbacks[i].Callback();
                    }
                }
            }
            gcode::clearBuffer();
        }

        if(inChar == '\n')
        {
            // run
            runCallback();
            return;
        }

        if(inChar >= 'A' && inChar <= 'Z')
        {
            gcode::clearBuffer();
            commadLetter = inChar;
            return;
        }
        
        if((inChar >= '0' && inChar <= '9') || inChar == '.' || inChar == '-')
        {
            commandBuffer = commandBuffer + String(inChar);
            return;
        }
    }
}






void gcode::setCommand(char commandLetter, void (*CallBack)())
{
    //commandscallback* myarray = malloc(sizeof(commandscallbacks));
    commandscallback* commandscallbacks_temp = realloc(commandscallbacks, sizeof(commandscallbacks) + sizeof(commandscallback));
    if (commandscallbacks_temp) 
    {
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].letter = commandLetter;
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].includesValue = 0;
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].Callback = CallBack;
    }
    else
    {
        // deal with realloc failing because memory could not be allocated.
    }
}

void gcode::setCommand(char commandLetter, double value, void (*CallBack)())
{
    //commandscallback* myarray = malloc(sizeof(commandscallbacks));
    commandscallback* commandscallbacks_temp = realloc(commandscallbacks, sizeof(commandscallbacks) + sizeof(commandscallback));
    if (commandscallbacks_temp) 
    {
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].letter = commandLetter;
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].value = value;
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].includesValue = 1;
        commandscallbacks_temp[sizeof(commandscallbacks)/sizeof(commandscallback)-1].Callback = CallBack;
    }
    else
    {
        // deal with realloc failing because memory could not be allocated.
    }
}

void gcode::comment(String comment)
{
  Serial.println(";" +String(comment));
}

void gcode::command(char number, double values)
{
  Serial.println(String(number)+String(values));
}

double gcode::GetValue(char commandLetter)
{
    if(commadLetter == 0)
    {
        return commandsList[0];
    }
    else if(commadLetter >= 'A' && commadLetter <= 'Z')
    {
        return commandsList[commadLetter - 'A' + 1];
    }
    return 0;
}