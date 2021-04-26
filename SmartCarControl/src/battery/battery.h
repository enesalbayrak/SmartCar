#ifndef BATTERY_H
#define BATTERY_H
#include <stdint.h>
#define BATTERY_DEFAULT_PERCENT 95
#define BATTERY_DEFAULT_RES_1 10000.0
#define BATTERY_DEFAULT_RES_2 992.0
#define BATTERY_DEFAULT_MAX_VALUE 8.40
#define BATTERY_DEFAULT_MIN_VALUE 6.40

class Battery
{
private:
    uint8_t pin;
    float minValue;
    float maxValue;
    float res1;
    float res2;
    float errorPercent;
public:
    Battery(uint8_t pin,float minValue=BATTERY_DEFAULT_MIN_VALUE,float maxValue=BATTERY_DEFAULT_MAX_VALUE,float res1=BATTERY_DEFAULT_RES_1,float res2=BATTERY_DEFAULT_RES_2);
    uint8_t percent();
};
#endif