#include "movementlogger.h"
#include<Arduino.h>
void MovementLogger::inLogger(bool in0,bool in1,bool in2){
    String printText="in data:";
    printText+=in2?"1":"0";
    printText+=in1?"1":"0";
    printText+=in0?"1":"0";
    Serial.println(printText);
}

void MovementLogger::motorLogger(bool leftActive,bool leftDir,bool rightActive,bool rightDir){
    String printText="move data";
    
    printText+="\tleft active:";
    printText+=leftActive?"1":"0";
    printText+="\tleft:";
    printText+=leftDir?"1":"0";
    Serial.print(printText);
    printText="";
    printText+="\tright active:";
    printText+=rightActive?"1":"0";
    printText+="\tright:";
    printText+=rightDir?"1":"0";

    Serial.println(printText);
}

MovementLogger::MovementLogger(){}

MovementLogger::~MovementLogger(){}