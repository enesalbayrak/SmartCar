#ifndef LIGHTSTATUS_H
#define LIGHTSTATUS_H
#include<enums.h>

struct LightStatus
{
    uint8_t headLightPercent;
    LightStatusType backHeadLight;
    LightStatusType backLight;
    SignalStatusType signalStatus;
};

#endif