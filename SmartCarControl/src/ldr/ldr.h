#ifndef LDR_H
#define LDR_H
#include<stdint.h>
class Ldr
{
private:
uint8_t pin;
public:
    Ldr(uint8_t pin);
    uint8_t percent();
};


#endif