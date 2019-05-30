
#ifndef gcode_h
#define gcode_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


#define gcode_Buffer_version 2.0

#ifndef gcode_Buffer_size
    #define gcode_Buffer_size 20
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
        bool availableValue(char commandLetter);
        double GetValue(char commandLetter);
        void clearBuffer();
        
    private:
        String nextComandcommentString;
        bool nextRead = false;
        bool restIsComment = false;

        commandscallback *commandscallbacks; 
        int NumberOfCommands = 0;

        CallbackFunction runCallback;
        //double commandsList[gcode_Buffer_size];
        String commandBuffer;
        struct BufferFormat {
            char command;
            double Value;
        } BufferList[gcode_Buffer_size];
        int BufferListCount = -1;
        
};

#endif 
