
#ifndef gcode_h
#define gcode_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

class gcode
{
    public:
        // SETUP 
        gcode();
        gcode(int bitrate);
        gcode(void (*CallBack)());
        gcode(int bitrate,void (*CallBack)());
        void setCommand(char commandLetter, void (*CallBack)(double value));
        void setCommand(char commandLetter, double value, void (*CallBack)());

        // SEND 
        void comment(String comment);
        void command(char number, double values);
        
        // receive
        void read();
        double GetValue(char commandLetter);
        
    private:

    char commadLetter = 0;
    string commandBuffer = "";
    double commandValue = 0;
    double commandsList[27];
    
    typedef void (*CallbackFunction) ();
    CallbackFunction runCallback;

    struct commandscallback {
        char letter;
        double value;
        boolean includesValue;
        CallbackFunction Callback;
    } commandscallbacks[0];
    
    void clearBuffer()
};

#endif 
