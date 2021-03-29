#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include<stdint.h>
class LightControl
{
private:
    uint8_t pinAddress;
public:
    LightControl(uint8_t pinAddress);
    void open(uint8_t percent=100);
    void close();
};
#endif