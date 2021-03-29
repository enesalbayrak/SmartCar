#ifndef SIGNALLIGHT_H
#define SIGNALLIGHT_H
#include<loopcontrol.h>
#include<stdint.h>
class SignalLight
{
 #define DEFAULT_SIGNAL_TIME 500
    public:
    SignalLight(uint8_t pinAddress,uint16_t lowTime=DEFAULT_SIGNAL_TIME,uint16_t highTime=DEFAULT_SIGNAL_TIME,bool firstHigh=true);
    void start();
    void stop();
    void control();
    private:
        uint8_t pinAddress;
        uint16_t lowTime;
        uint16_t highTime;
        bool firstHigh;
        bool active=false;
        unsigned long lastMillis;
        uint8_t lightStatus;
};

#endif // SIGNALLIGHT_H
