#include"signallight.h"

#include<Arduino.h>
SignalLight::SignalLight(uint8_t pinAddress,uint16_t lowTime,uint16_t highTime,bool firstHigh){
    this->pinAddress=pinAddress;
    this->lowTime=lowTime;
    this->highTime=highTime;
    this->firstHigh=firstHigh;
    pinMode(pinAddress,OUTPUT);
}

void SignalLight::start(){
    active=true;
    lastMillis=millis();
    lightStatus=firstHigh?HIGH:LOW;
}

void SignalLight::open(){
    active=false;
    digitalWrite(pinAddress,HIGH);
}


void SignalLight::stop(){
    active=false;
    digitalWrite(pinAddress,LOW);
}

void SignalLight::control(){
    if(active){
        long diff=millis()-lastMillis;
        bool write=true;
        if(lightStatus==HIGH&&diff>=highTime)
        {
            lightStatus=LOW;
        }
        else if(lightStatus==LOW&&diff>=lowTime)
        {
            lightStatus=HIGH;
        }
        else
            write=false;
        
        if(write)
        {
            digitalWrite(pinAddress,lightStatus);
            lastMillis=millis();
        }

    }
}
