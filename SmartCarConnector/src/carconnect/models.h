#include<enums.h>
struct CarControlData{
    LightStatusType leftSignal;
    LightStatusType rightSignal;
    LightStatusType headLight;
    LightStatusType longHeadLight;
    LightStatusType backLight;
    LightStatusType quadSignal;
    BuzzerSignalLevel buzzerLevel;
};

struct CarSensorData
{
    uint8_t batteryLevel;
    uint8_t lightLevel;
};
