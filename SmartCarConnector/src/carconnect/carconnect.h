#ifndef CARCONNECT_H
#define CARCONNECT_H
#include "models.h"
class CarConnect
{
private:
    /* data */
public:
    CarConnect();
    CarSensorData *communicate(CarControlData *data);
};
#endif