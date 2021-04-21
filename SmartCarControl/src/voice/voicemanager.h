#ifndef VOICE_H
#define VOICE_H
#include<stdint.h>
#include "buzersignal.h"
class VoiceManager
{
private:
    BuzzerSignal *signal;
    BuzzerSignalLevel oldLevel;
    bool parkActivity=false;
    bool hornActivity=false;
    void selectLevel(bool parkActivity,bool hornActivity,uint16_t backDistance,uint16_t frontDistance);
public:
    VoiceManager(uint8_t bzrPin);
    ~VoiceManager();
    bool getParkActivity();
    void control();
    void set(bool parkActivity,bool hornActivity,uint16_t backDistance,uint16_t frontDistance);
    void set(uint16_t backDistance,uint16_t frontDistance);
};


#endif