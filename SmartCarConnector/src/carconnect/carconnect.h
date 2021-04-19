#ifndef CARCONNECT_H
#define CARCONNECT_H
#include "models.h"
class CarConnect
{
private:
public:
    CarConnect();
    void send(CarControlData *data);
    CarSensorData *receive();
};
#endif