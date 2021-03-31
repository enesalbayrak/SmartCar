#ifndef CARMANAGER_H
#define CARMANAGER_H
#include <car/carlighting.h>
#include <carconnect/carconnect.h>
class CarManager:IDataManager
{
private:
    CarLighting *carLights;
public:
    void bindData(CarControlData *data) override;
    CarSensorData *getData() override;
    CarManager();
    void loop();
};

#endif