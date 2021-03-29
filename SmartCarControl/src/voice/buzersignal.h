#ifndef BUZZERSIGNAL_H
#define BUZZERSIGNAL_H
#include<stdint.h>
#include<loopcontrol.h>
enum BuzzerSignalLevel{
    CLOSE=0,
    LEVEL1=1,
    LEVEL2=2,
    LEVEL3=3,
    OPEN=4
};
class BuzzerSignal:public LoopControl
{
private:
    uint8_t pinAddress;
    uint8_t highTime;
    uint8_t lowTime;
    bool loopActive=false;
    unsigned long lastMillis;
    BuzzerSignalLevel level=BuzzerSignalLevel::CLOSE;
    uint8_t buzzerStatus;
public:
    BuzzerSignal(uint8_t pinAddress);
    void setLevel(BuzzerSignalLevel level);
    void control() override;
};

#endif