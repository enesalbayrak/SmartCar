#ifndef CARMANAGER_H
#define CARMANAGER_H
#include <client/carclient.h>
#include <carconnect/carconnect.h>
#include <control/movement.h>

class CarManager
{
private:
    CarClient *client;
    CarConnect *connect;
    CarData *carData;
    CarControlData *controlData;
    Movement *movement;
    long lastMillis;
    void receiveSensorData();
public:
    CarManager();
    ~CarManager();
    void start();
    void control();
};

#endif