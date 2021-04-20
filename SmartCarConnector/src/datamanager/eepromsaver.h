#ifndef EEPROMSAVER_H
#define EEPROMSAVER_H
#include"connectdata.h"
class EEPROMSaver
{
private:
public:
    EEPROMSaver();
    ~EEPROMSaver();
    ConnectData *read();
    void write(ConnectData *data);
};

#endif