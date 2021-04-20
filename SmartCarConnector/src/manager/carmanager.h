#ifndef CARMANAGER_H
#define CARMANAGER_H
#include <client/carclient.h>
#include <carconnect/carconnect.h>
#include <control/movement.h>
#include <datamanager/idataconnector.h>
#include <datamanager/serialdataconnector.h>
#include <datamanager/eepromsaver.h>

class CarManager:private IDataConnector
{
private:
    bool usbMode=false;
    CarClient *client;
    CarConnect *carConnect;
    CarData *carData;
    CarControlData *controlData;
    Movement *movement;
    EEPROMSaver saver;
    long lastMillis;
    void receiveSensorData();
    ConnectData *connectData;
    SerialDataConnector *serialconnector;
    ConnectData *getData() override;
    void dataChanged(ConnectData *data) override;
    void save() override;
    void connect() override;
    void startMode() override;
    void restart() override;
    bool carIsActive();
public:
    CarManager();
    ~CarManager();
    void start();
    void control();
};

#endif