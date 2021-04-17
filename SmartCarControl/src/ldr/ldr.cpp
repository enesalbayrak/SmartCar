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
    Serial.println(value);
    if(value<LDR_MIN_VALUE)
        value=LDR_MIN_VALUE;
    else if(value>LDR_MAX_VALUE)
        value=LDR_MAX_VALUE;
    return map(value,LDR_MIN_VALUE,LDR_MAX_VALUE,0,100);
}