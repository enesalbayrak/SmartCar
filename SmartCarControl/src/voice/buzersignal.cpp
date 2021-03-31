#include "buzersignal.h"
#include <Arduino.h>
#define LEVEL_1_HIGH_TIME 500
#define LEVEL_2_HIGH_TIME 400
#define LEVEL_3_HIGH_TIME 300
#define LEVEL_1_LOW_TIME 200
#define LEVEL_2_LOW_TIME 160
#define LEVEL_3_LOW_TIME 120
BuzzerSignal::BuzzerSignal(uint8_t pinAddress)
{
    this->pinAddress=pinAddress;
    pinMode(pinAddress,OUTPUT);
    buzzerStatus=LOW;
}

void BuzzerSignal::setLevel(BuzzerSignalLevel level){
    this->level=level;
    lastMillis=millis();
    switch (level)
    {
    case BUZZER_LEVEL1:
        highTime=LEVEL_1_HIGH_TIME;
        lowTime=LEVEL_1_LOW_TIME;
        loopActive=true;
        buzzerStatus=HIGH;
        break;
    case BUZZER_LEVEL2:
        highTime=LEVEL_2_HIGH_TIME;
        lowTime=LEVEL_2_LOW_TIME;
        loopActive=true;
        buzzerStatus=HIGH;
        break;
    case BUZZER_LEVEL3:
        highTime=LEVEL_3_HIGH_TIME;
        lowTime=LEVEL_3_LOW_TIME;
        loopActive=true;
        buzzerStatus=HIGH;
        break;
    case BUZZER_OPEN:
        loopActive=false;
        buzzerStatus=HIGH;
        break;
    
    case BUZZER_CLOSE:
        loopActive=false;
        buzzerStatus=LOW;
        break;
    
    }
    digitalWrite(pinAddress,buzzerStatus);

}
void BuzzerSignal::control()
{
    if(loopActive){
        long diff=millis()-lastMillis;
        bool write=true;
        if(buzzerStatus==HIGH&&diff>=highTime)
        {
            buzzerStatus=LOW;
        }
        else if(buzzerStatus==LOW&&diff>=lowTime)
        {
            buzzerStatus=HIGH;
        }
        else
            write=false;
        
        if(write)
        {
            digitalWrite(pinAddress,buzzerStatus);
            lastMillis=millis();
        }

    }
}