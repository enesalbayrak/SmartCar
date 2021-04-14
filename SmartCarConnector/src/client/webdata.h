#ifndef WEBDATA_H
#define WEBDATA_H
#include <enums.h>
struct WebData
{
    MovementDirection movementDirection;
    LightStatusType headLight;
    LightStatusType longHeadLight;
    LightStatusType backLight;
    SignalStatusType signalStatus;
    bool parkActivity;
    bool hornActivity;
};

#endif