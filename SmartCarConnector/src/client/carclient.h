#ifndef CLIENT_H
#define CLIENT_H
#include"webdata.h"
#include"cardata.h"
#include<Arduino.h>
class CarClient
{
private:
    String ssid;
    String password;
    String key;
public:
    CarClient();
    bool connectWifi(String ssid,String password);
    bool connectApi(String key);
    WebData *getData(CarData *carData);
};
#endif
