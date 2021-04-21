#include "voicemanager.h"
#include<Arduino.h>
#define BUZZER_LEVEL_1_DISTANCE_MM 200
#define BUZZER_LEVEL_2_DISTANCE_MM 125
#define BUZZER_LEVEL_3_DISTANCE_MM 75
#define BUZZER_LEVEL_O_DISTANCE_MM 50
VoiceManager::VoiceManager(uint8_t bzrPin)
{
    this->signal= new BuzzerSignal(bzrPin);
}

VoiceManager::~VoiceManager()
{
    delete signal;
}

bool VoiceManager::getParkActivity()
{
    return this->parkActivity;
}

void VoiceManager::selectLevel(bool parkActivity,bool hornActivity,uint16_t backDistance,uint16_t frontDistance)
{
    BuzzerSignalLevel level;
    if(hornActivity)
    {
        level=BuzzerSignalLevel::BUZZER_OPEN;
    }
    else if(!parkActivity)
    {
        level=BuzzerSignalLevel::BUZZER_CLOSE;
    }
    else{
            uint16_t minDistance=backDistance <= frontDistance? backDistance :frontDistance;
            if(minDistance<=BUZZER_LEVEL_O_DISTANCE_MM)
                level=BuzzerSignalLevel::BUZZER_OPEN;
            else if(minDistance<=BUZZER_LEVEL_3_DISTANCE_MM)
                level=BuzzerSignalLevel::BUZZER_LEVEL3;
            else if(minDistance<=BUZZER_LEVEL_2_DISTANCE_MM)
                level=BuzzerSignalLevel::BUZZER_LEVEL2;
            else if(minDistance<=BUZZER_LEVEL_1_DISTANCE_MM)
                level=BuzzerSignalLevel::BUZZER_LEVEL1;
            else
                level=BuzzerSignalLevel::BUZZER_CLOSE;
    }

    if(this->oldLevel==level)
        return;
    signal->setLevel(level);
    oldLevel=level;
    signal->control();
}

void VoiceManager::set(bool parkActivity,bool hornActivity,uint16_t backDistance,uint16_t frontDistance)
{
   this->hornActivity=hornActivity;
   this->parkActivity=parkActivity;
   selectLevel(parkActivity,hornActivity,backDistance,frontDistance);
}

void VoiceManager::set(uint16_t backDistance,uint16_t frontDistance)
{
   selectLevel(parkActivity,hornActivity,backDistance,frontDistance);
}

void VoiceManager::control()
{
    signal->control();
}