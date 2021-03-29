#ifndef CARLIGHTING_H
#define CARLIGHTING_H
#include "lighting/signallight.h"
#include "lighting/lightcontrol.h"
#include "lightstatus.h"
#include "loopcontrol.h"
class CarLighting:public LoopControl
{
private:
    LightControl *backLight;
    LightControl *headLight;
    SignalLight *leftSignal;
    SignalLight *rightSignal;
    LightStatus status;
public:
    CarLighting();
    void setLightStatus(LightStatus status);
    LightStatus getLightStatus();
    void control() override;
};

#endif