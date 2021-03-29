#include"lightcontrol.h"
#include<Arduino.h>
LightControl::LightControl(uint8_t pinAddress)
{
    this->pinAddress=pinAddress;
    pinMode(pinAddress,OUTPUT);
}

void LightControl::open(uint8_t percent){
    if(percent>100)
        percent=100;
    uint8_t value=map(percent,0,100,0,255);
    analogWrite(pinAddress,value);
}
void LightControl::close()
{
    analogWrite(pinAddress,LOW);
}