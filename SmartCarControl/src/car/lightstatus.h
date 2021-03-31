#ifndef LIGHTSTATUS_H
#define LIGHTSTATUS_H
#include<enums.h>

struct LightStatus
{
    LightStatusType LeftSignal;
    LightStatusType RightSignal;
    LightStatusType HeadLight;
    LightStatusType LongHeadLight;
    LightStatusType BackLight;
    LightStatusType QuadSignal;
};

#endif