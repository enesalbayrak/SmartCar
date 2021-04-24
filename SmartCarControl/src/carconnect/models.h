#ifndef MODELS_H
#define MODELS_H
#include<enums.h>
struct CarControlData{
    SignalStatusType signalStatus;
    uint8_t headLightPercent;
    LightStatusType backHeadLight;
    LightStatusType backLight;
    BuzzerSignalLevel buzzerStatus;
};

struct CarSensorData
{
    uint8_t batteryLevel;
    uint8_t lightLevel;
    uint16_t frontDistance;
    uint16_t backDistance;
};
#endif