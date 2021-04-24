#ifndef WEBDATA_H
#define WEBDATA_H
#include <enums.h>
struct WebData
{
    MovementDirection movementDirection;
    uint8_t headLightPercent;
    LightStatusType backLight;
    LightStatusType backHeadLight;
    SignalStatusType signalStatus;
    BuzzerSignalLevel buzzerStatus;
};

#endif