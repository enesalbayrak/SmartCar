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
    SIGNAL_QUAD=3
};

enum BuzzerSignalLevel:uint8_t{
    BUZZER_CLOSE=0,
    BUZZER_LEVEL1=1,
    BUZZER_LEVEL2=2,
    BUZZER_LEVEL3=3,
    BUZZER_OPEN=4
};

enum MovementDirection:uint8_t{
    PASSIVE=0,
    FRONT_LEFT=1,
    FRONT=2,
    FRONT_RIGHT=3,
    ANTI_CLOCKWISE=4,
    CLOCKWISE=5,
    BACK_LEFT=6,
    BACK=7,
    BACK_RIGHT=8
};

#endif