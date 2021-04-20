#ifndef IDATACONNECTOR_H
#define IDATACONNECTOR_H
#include "connectdata.h"
class IDataConnector
{
public:
    virtual ConnectData *getData()=0;
    virtual void dataChanged(ConnectData *data)=0;
    virtual void startMode()=0;
    virtual void save()=0;
    virtual void connect()=0;
    virtual void restart()=0;
};

#endif