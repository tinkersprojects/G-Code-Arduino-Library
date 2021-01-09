
#ifndef gcode_h
#define gcode_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


#define gcode_Buffer_version 2.1

#ifndef gcode_Buffer_size
    #define gcode_Buffer_size 5
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
        void begin(unsigned long baud);
        void begin(String nextComandcomment);
        void begin(unsigned long baud, String nextComandcomment);
        void begin(void (*_nextComandCallBack)());
        void begin(unsigned long baud, void (*_nextComandCallBack)());

        // SEND 
        void comment(String comment);
        void comment(char number, double values);
        void command(char number, double values);
        
        // receive
        bool available();
        bool available(char inChar);
        bool availableValue(char commandLetter);
        double GetValue(char commandLetter);
        void clearBuffer();
        
        struct BufferFormat {
            char command;
            double Value;
        } BufferList[gcode_Buffer_size];

    private:
        String nextComandcommentString;
        bool nextRead = false;
        bool restIsComment = false;

        commandscallback *commandscallbacks; 
        int NumberOfCommands = 0;

        CallbackFunction runCallback;
        CallbackFunction nextComandCallBack = NULL;
        //double commandsList[gcode_Buffer_size];
        String commandBuffer;
       /* struct BufferFormat {
            char command;
            double Value;
        } BufferList[gcode_Buffer_size];*/
        int BufferListCount = 0;
        int BufferListstart = 0;
        
};

#endif 
