#ifndef SERIALDATA_H
#define SERIALDATA_H
#include "idataconnector.h"
class SerialDataConnector
{
private:
    IDataConnector *connector;
    ConnectData *data;
    bool started=false;
public:
    SerialDataConnector(IDataConnector *connector);
    void read();
};

#endif