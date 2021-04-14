#ifndef LIGHTSTATUS_H
#define LIGHTSTATUS_H
#include<enums.h>

struct LightStatus
{
    LightStatusType HeadLight;
    LightStatusType LongHeadLight;
    LightStatusType BackLight;
    SignalStatusType SignalStatus;
};

#endif