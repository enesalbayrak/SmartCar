#include "carlighting.h"
#include "definations.h"
CarLighting::CarLighting()
{
    this->backLight=new LightControl(BACKLIGHT_PIN);
    this->headLight=new LightControl(HEADLIGHT_PIN);
    this->headLight->close();
    this->backHeadLight=new LightControl(BACK_HEADLIGHT_PIN);
    this->leftSignal=new SignalLight(SIGNAL_LEFT_PIN);
    this->rightSignal=new SignalLight(SIGNAL_RIGHT_PIN);
}

void CarLighting::setLightStatus(LightStatus status)
{
    if(this->status.backLight!=status.backLight)
    {
        if(status.backLight==LightStatusType::LIGHT_OPEN)
            backLight->open();
        else
            backLight->close();
    }

    if(this->status.backHeadLight!=status.backHeadLight)
    {
        if(status.backHeadLight==LightStatusType::LIGHT_OPEN)
            backHeadLight->open();
        else
            backHeadLight->close();
    }

    if(this->status.headLightPercent!=status.headLightPercent)
    {
        headLight->open(status.headLightPercent);
    }
    if(this->status.signalStatus!=status.signalStatus)
    {
        switch (status.signalStatus)
        {
        case SIGNAL_OPEN:
        leftSignal->open();
        rightSignal->open();
        break;
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