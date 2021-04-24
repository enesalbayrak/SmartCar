#include "ldr.h"
#include<Arduino.h>
#define LDR_MIN_VALUE 1.0
#define LDR_MAX_VALUE 1024.0
double max=log10(LDR_MAX_VALUE);
Ldr::Ldr(uint8_t pin){
    this->pin=pin;
    pinMode(pin,INPUT);
}

uint8_t Ldr::percent(){
    int value=analogRead(pin);
    if(value<LDR_MIN_VALUE)
        value=LDR_MIN_VALUE;
    else if(value>LDR_MAX_VALUE)
        value=LDR_MAX_VALUE;
    double x=((float)value)/LDR_MAX_VALUE;
    double y=sqrt(1-pow(x-1,2));
    return round(y*100);
}