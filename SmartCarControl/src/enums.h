#ifndef ENUMS_H
#define ENUMS_H
#include<stdint.h>

enum LightStatusType:uint8_t{
    LIGHT_CLOSE=0,
    LIGHT_OPEN=1
};

enum SignalStatusType:uint8_t{
    SIGNAL_CLOSE=0,
    SIGNAL_LEFT=1,
    SIGNAL_RIGHT=2,
    SIGNAL_QUAD=3,
    SIGNAL_OPEN=4
};

enum BuzzerSignalLevel:uint8_t{
    BUZZER_CLOSE=0,
    BUZZER_LEVEL1=1,
    BUZZER_LEVEL2=2,
    BUZZER_LEVEL3=3,
    BUZZER_OPEN=4
};

#endif