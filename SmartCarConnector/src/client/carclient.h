#ifndef CLIENT_H
#define CLIENT_H
#include"webdata.h"
#include"cardata.h"
class CarClient
{
private:
    char *ssid;
    char *password;
    char *key;
public:
    CarClient(char * ssid,char *password,char *key);
    bool connectWifi();
    bool connectApi();
    WebData *getData(CarData *carData);
};
#endif
