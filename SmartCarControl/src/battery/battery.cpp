#include "battery.h"
#include <Arduino.h>
#include<math.h>

Battery::Battery(uint8_t pin,float minValue,float maxValue,float res1,float res2, float errorPercent)
{
    this->pin=pin;
    this->minValue=minValue;
    this->maxValue=maxValue;
    this->res1=res1;
    this->res2=res2;
    this->errorPercent=errorPercent;
    pinMode(pin,INPUT);
}

uint8_t Battery::percent(){
    float value=0;
    for (size_t i = 0; i < 100; i++)
    {
        value+=analogRead(pin);
        delayMicroseconds(10);
    }
    
    value /=100; 
    double vout = (value * 5.0) / 1024.0; // see text
    double vin = (vout*(1+errorPercent)*(res1+res2)) / res2; 
   if(vin<minValue)
    vin=minValue;
    else if(vin>maxValue)
    vin=maxValue;
   return (uint8_t)(round(100*((vin-minValue)/(maxValue-minValue))));
}