#ifndef MODELS_H
#define MODELS_H
#include<enums.h>
struct CarControlData{
    SignalStatusType signalStatus;
    LightStatusType headLight;
    LightStatusType longHeadLight;
    LightStatusType backLight;
    bool parkActivity;
    bool hornActivity;
};

struct CarSensorData
{
    uint8_t batteryLevel;
    uint8_t lightLevel;
    uint16_t frontDistance;
    uint16_t backDistance;
};
#endif