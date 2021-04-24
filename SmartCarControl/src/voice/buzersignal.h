#ifndef BUZZERSIGNAL_H
#define BUZZERSIGNAL_H
#include<stdint.h>
#include<enums.h>
class BuzzerSignal
{
private:
    uint8_t pinAddress;
    uint8_t highTime;
    uint8_t lowTime;
    bool loopActive=false;
    unsigned long lastMillis;
    BuzzerSignalLevel level=BuzzerSignalLevel::BUZZER_CLOSE;
    uint8_t buzzerStatus;
public:
    BuzzerSignal(uint8_t pinAddress);
    void setLevel(BuzzerSignalLevel level);
    void control();
};

#endif