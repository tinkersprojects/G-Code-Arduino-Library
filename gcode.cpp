/**********************************************************************************************
 * Arduino LED RGB Library - version 2.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "gcode.h"

/******************* SETUP *******************/

gcode::gcode()
{
  NumberOfCommands = 0;
}

gcode::gcode(int numbercommands, commandscallback *commandscallbacks_temp, void (*CallBack)())
{
  runCallback = CallBack;
  commandscallbacks = commandscallbacks_temp;
  NumberOfCommands = numbercommands;
}

gcode::gcode(int numbercommands, commandscallback *commandscallbacks_temp)
{
  commandscallbacks = commandscallbacks_temp;
  NumberOfCommands = numbercommands;
}
        
gcode::gcode(void (*CallBack)())
{
  runCallback = CallBack;
}

void gcode::begin()
{
  Serial.begin(9600);
  Serial.println("v" +String(gcode_Buffer_version)+" Simple G code");
  nextComandcommentString = "OK!";
  this->clearBuffer();
}

void gcode::begin(String nextComandcomment)
{
  Serial.begin(9600);
  Serial.println("v" +String(gcode_Buffer_version)+" Simple G code");
  nextComandcommentString = nextComandcomment;
  this->clearBuffer();
}

void gcode::begin(int bitrate)
{
  Serial.begin(bitrate);
  Serial.println("v" +String(gcode_Buffer_version)+" Simple G code");
  nextComandcommentString = "OK!";
  this->clearBuffer();
}

void gcode::begin(int bitrate, String nextComandcomment)
{
  Serial.begin(bitrate);
  Serial.println("v" +String(gcode_Buffer_version)+" Simple G code");
  nextComandcommentString = nextComandcomment;
  this->clearBuffer();
}


/******************* receive *******************/

void gcode::clearBuffer()
{
  BufferListCount = -1;
  for(int i = 0; i < gcode_Buffer_size; i++)
  {
    BufferList[i].command = 0;
    BufferList[i].Value = 0;
  }
}

bool gcode::available()
{
  if(nextRead)
  {
    this->comment(nextComandcommentString);
    nextRead = false;
    restIsComment = false;
    this->clearBuffer();
  }
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    if(this->available(inChar))
    {
      return true;
    }
  }
  return false;
}

bool gcode::available(char inChar)
{
  if(inChar == ' ')
    return false;

  if(inChar == '\n')
  {
    nextRead=true;
    restIsComment = false;
    if(BufferListCount >= 0)
      BufferList[BufferListCount].Value = commandBuffer.toDouble(); 

    for(int i = 0; i < gcode_Buffer_size; i++)
    {
      String testString = String(BufferList[i].command)+String(((int)BufferList[i].Value));

      for(int j = 0; j < NumberOfCommands; j++)
      {
        commandscallback commandscallbackstest = commandscallbacks[j];
        
        if(testString == commandscallbackstest.value)
        {
          commandscallbackstest.Callback();
        }
      }
    }
    if(runCallback != NULL)
      runCallback();
    return true;
  }

  if(inChar == ';' || restIsComment)
  {
    restIsComment = true;
    return false;
  }

  if((inChar >= '0' && inChar <= '9') || inChar == '.' || inChar == '-')
  {
    commandBuffer = commandBuffer + String(inChar);
  }
  else if(inChar > 32 && inChar < 127)
  {
    if(inChar >= 'a' && inChar <= 'z')
    {
      inChar = inChar - ('a'-'A');
    }

    if(BufferListCount+1 >= gcode_Buffer_size)
      return false;

    if(BufferListCount >= 0)
      BufferList[BufferListCount].Value = commandBuffer.toDouble(); 
    else if(commandBuffer.toDouble()>0)
    {
      BufferListCount = 0;
      BufferList[BufferListCount].command = 0;  
      BufferList[BufferListCount].Value = commandBuffer.toDouble(); 
    }

    commandBuffer = "";

    BufferListCount++;
    BufferList[BufferListCount].command = inChar;    
  }

  return false;
/*
    if((inChar >= 'A' && inChar <= 'Z') || (inChar >= 'a' && inChar <= 'z') || inChar == ' ' || inChar == '\n')
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

            for(int i = 0; i < NumberOfCommands; i++)
            {
                commandscallback commandscallbackstest = commandscallbacks[i];

                if(commandscallbackstest.value == String(commandLetter)+String(commandBuffer) || commandscallbackstest.value == String(commandLetter-('a'-'A'))+String(commandBuffer))
                {
                    commandscallbackstest.Callback();
                }
            }
        }
        this->clearBuffer();
    }*/
/*
    if(inChar == ';' || restIsComment)
    {
        restIsComment = true;
        return false;
    }*/
/*
    if(inChar >= 'a' && inChar <= 'z')
    {
        inChar = inChar - ('a'-'A');
    }

    if(inChar >= 'A' && inChar <= 'Z')
    {
        this->clearBuffer();
        commandLetter = inChar;
        return false;
    }*/
}

bool gcode::availableValue(char commandLetter)
{
  for(int i = 0; i < gcode_Buffer_size; i++)
  {
    if(BufferList[i].command == commandLetter)
      return true;
  }
  return false;
}

double gcode::GetValue(char commandLetter)
{
  for(int i = 0; i < gcode_Buffer_size; i++)
  {
    if(BufferList[i].command == commandLetter)
      return BufferList[i].Value;
  }
  return 0;
}

void gcode::comment(String comment)
{
  Serial.println(comment);
}

void gcode::command(char number, double values)
{
  Serial.println(String(number)+String(values));
}