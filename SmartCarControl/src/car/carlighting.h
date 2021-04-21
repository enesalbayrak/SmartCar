#ifndef CARLIGHTING_H
#define CARLIGHTING_H
#include "lighting/signallight.h"
#include "lighting/lightcontrol.h"
#include "lightstatus.h"
#include "loopcontrol.h"
class CarLighting
{
private:
    LightControl *backLight;
    LightControl *headLight;
    LightControl *backHeadLight;
    SignalLight *leftSignal;
    SignalLight *rightSignal;
    LightStatus status;
public:
    CarLighting();
    void setLightStatus(LightStatus status);
    LightStatus getLightStatus();
    void control();
};

#endif