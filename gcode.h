
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
        gcode(commandscallback *commandscallbacks_temp);
        void begin();
        void begin(int bitrate);

        // SEND 
        void comment(String comment);
        void command(char number, double values);
        
        // receive
        bool available();
        bool available(char inChar);
        double GetValue(char commandLetter);
        void clearBuffer();
        
    private:
    
        commandscallback *commandscallbacks; 
        CallbackFunction runCallback;
        bool restIsComment = false;
        char commandLetter = 0;
        String commandBuffer = "";
        double commandValue = 0;
        double commandsList[27];
        
};

#endif 
