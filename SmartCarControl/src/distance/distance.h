#ifndef DISTANCE_H
#define DISTANCE_H
#include<stdint.h>
class Distance
{
private:
    uint8_t echoPin;
    uint8_t trigPin;
public:
    Distance(uint8_t echoPin,uint8_t trigPin);
    uint16_t readDistance();
    ~Distance();
};

#endif