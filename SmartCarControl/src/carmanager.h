#ifndef CARMANAGER_H
#define CARMANAGER_H
#include <car/carlighting.h>
#include <carconnect/carconnect.h>
#include <ldr/ldr.h>
#include <battery/battery.h>
#include <distance/distance.h>
#include"voice/voicemanager.h"
class CarManager:IDataManager
{
private:
    CarLighting *carLights;
    Ldr *ldr;
    Battery *battery;
    Distance *backDistance;
    Distance *frontDistance;
    VoiceManager * voiceManager;
public:
    void bindData(CarControlData *data) override;
    CarSensorData *getData() override;
    CarManager();
    void loop();
};

#endif