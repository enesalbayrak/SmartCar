#ifndef ENUMS_H
#define ENUMS_H
#include<stdint.h>

enum LightStatusType:uint8_t{
    LIGHT_CLOSE=0,
    LIGHT_OPEN=1
};
enum BuzzerSignalLevel:uint8_t{
    BUZZER_CLOSE=0,
    BUZZER_LEVEL1=1,
    BUZZER_LEVEL2=2,
    BUZZER_LEVEL3=3,
    BUZZER_OPEN=4
};

enum MovementDirection:uint8_t{
    PASSIVE=0xff,
    FRONT_LEFT=0x00,
    FRONT=0x01,
    FRONT_RIGHT=0x02,
    ANTI_CLOCKWISE=0x03,
    CLOCKWISE=0x04,
    BACK_LEFT=0x05,
    BACK=0x06,
    BACK_RIGHT=0x07
};

#endif