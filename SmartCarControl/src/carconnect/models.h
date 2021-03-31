#ifndef MODELS_H
#define MODELS_H
#include<enums.h>
struct CarControlData{
    uint8_t LeftMotorPower;
    uint8_t RightMotorPower;
    LightStatusType LeftSignal;
    LightStatusType RightSignal;
    LightStatusType HeadLight;
    LightStatusType LongHeadLight;
    LightStatusType BackLight;
    LightStatusType QuadSignal;
    BuzzerSignalLevel BuzzerLevel;
};

struct CarSensorData
{
    uint8_t BatteryLevel;
    uint8_t LightLevel;
};
#endif