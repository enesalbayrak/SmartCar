#ifndef WEBDATA_H
#define WEBDATA_H
#include <enums.h>
struct WebData
{
    MovementDirection movementDirection;
    LightStatusType leftSignal;
    LightStatusType rightSignal;
    LightStatusType headLight;
    LightStatusType longHeadLight;
    LightStatusType backLight;
    LightStatusType quadSignal;
    bool parkActivity;
    bool hornActivity;
};

#endif