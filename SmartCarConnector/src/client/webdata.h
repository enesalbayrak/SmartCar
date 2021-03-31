#ifndef WEBDATA_H
#define WEBDATA_H
#include <enums.h>
struct WebData
{
    int LeftMotorPower;
    int RightMotorPower;
    LightStatusType LeftSignal;
    LightStatusType RightSignal;
    LightStatusType HeadLight;
    LightStatusType LongHeadLight;
    LightStatusType BackLight;
    LightStatusType QuadSignal;
    bool ParkActivity;
    bool HornActivity;
};

#endif