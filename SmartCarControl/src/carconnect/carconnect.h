#ifndef CARCONNECT_H
#define CARCONNECT_H
#include"models.h"
class IDataManager{
    public:
    virtual CarSensorData *getData()=0;
    virtual void bindData(CarControlData *data)=0;
};
class CarConnect{
    private:
        CarConnect();
    public:
        static void connect(IDataManager *manager);
};

#endif