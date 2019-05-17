
#ifndef gcode_h
#define gcode_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


typedef void (*CallbackFunction) ();

typedef struct commandscallback {
    String value;
    CallbackFunction Callback;
};

class gcode
{
    public:
    

        // SETUP 
        gcode();
        gcode(void (*CallBack)());
        gcode(int numbercommands, commandscallback *commandscallbacks_temp);
        gcode(int numbercommands, commandscallback *commandscallbacks_temp, void (*CallBack)());
        void begin();
        void begin(int bitrate);
        void begin(String nextComandcomment);
        void begin(int bitrate, String nextComandcomment);

        // SEND 
        void comment(String comment);
        void command(char number, double values);
        
        // receive
        bool available();
        bool available(char inChar);
        double GetValue(char commandLetter);
        void clearBuffer();
        
    private:
        String nextComandcommentString;
        bool nextRead = false;
        commandscallback *commandscallbacks; 
        CallbackFunction runCallback;
        bool restIsComment = false;
        char commandLetter = 0;
        String commandBuffer = "";
        double commandValue = 0;
        double commandsList[27];
        int NumberOfCommands = 0;
        
};

#endif 
