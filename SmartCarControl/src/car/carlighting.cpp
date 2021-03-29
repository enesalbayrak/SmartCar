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
    this->status=status;
    if(status.BackLight==LightStatusType::OPEN)
        backLight->open();
    else
        backLight->close();

    if(status.HeadLight==LightStatusType::OPEN)
        headLight->open(status.LongHeadLight==LightStatusType::OPEN?LONG_HEADLIGHT_VALUE:SHORT_HEADLIGHT_VALUE);
    else
        headLight->close();

    if(status.QuadSignal==LightStatusType::OPEN){
        leftSignal->start();
        rightSignal->start();
    }
    else
    {
        if(status.LeftSignal==LightStatusType::OPEN)
            leftSignal->start();
        else
            leftSignal->stop();

        if(status.RightSignal==LightStatusType::OPEN)
            rightSignal->start();
        else
            rightSignal->stop();
    }
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