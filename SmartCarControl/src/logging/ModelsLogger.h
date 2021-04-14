#ifndef MODELSLOGGER_H
#define MODELSLOGGER_H
#include <carconnect/models.h>
class ModelsLogger
{
private:
public:
    ModelsLogger();
    static void log(CarControlData * data);
    static void log(CarSensorData * data);
};
#endif