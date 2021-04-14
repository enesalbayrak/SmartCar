#include "carlighting.h"
#include "definations.h"
CarLighting::CarLighting()
{
    this->backLight=new LightControl(BACKLIGHT_PIN);
    this->headLight=new LightControl(HEADLIGHT_PIN);
    this->leftSignal=new SignalLight(SIGNAL_LEFT_PIN);
    this->rightSignal=new SignalLight(SIGNAL_RIGHT_PIN);
}

void CarLighting::setLightStatus(LightStatus status)
{
    if(this->status.BackLight!=status.BackLight)
    {
        if(status.BackLight==LightStatusType::LIGHT_OPEN)
            backLight->open();
        else
            backLight->close();
    }

    if(this->status.HeadLight!=status.HeadLight||this->status.LongHeadLight!=status.LongHeadLight)
    {
        if(status.HeadLight==LightStatusType::LIGHT_OPEN)
            headLight->open(status.LongHeadLight==LightStatusType::LIGHT_OPEN?LONG_HEADLIGHT_VALUE:SHORT_HEADLIGHT_VALUE);
        else
            headLight->close();
    }
    
    if(this->status.SignalStatus!=status.SignalStatus)
    {
        switch (status.SignalStatus)
        {
        case SIGNAL_QUAD:
            leftSignal->start();
            rightSignal->start();
            break;
        case SIGNAL_LEFT:
            leftSignal->start();
            rightSignal->stop();
            break;
        case SIGNAL_RIGHT:
            leftSignal->stop();
            rightSignal->start();
            break;
        default:
            leftSignal->stop();
            rightSignal->stop();
            break;
        }
    }
    this->status=status;
}


LightStatus CarLighting::getLightStatus()
{
    return this->status;
}

void CarLighting::control()
{
    leftSignal->control();
    rightSignal->control();
}