#include"carconnect.h"
#include <Wire.h>
#include <stdlib.h>
#include <Arduino.h>
#include<logging/ModelsLogger.h>
#define I2C_CAR_CONNECTION_ADDRESS 41
IDataManager *_manager;
void receive(int count);
void request();
void CarConnect::connect(IDataManager *manager){
    _manager=manager;
    Wire.begin(I2C_CAR_CONNECTION_ADDRESS);
    Serial.println("Wire Started");
    Wire.onReceive(receive);
    Wire.onRequest(request);
}

void receive(int count){
  uint8_t* arr=(uint8_t*)malloc(sizeof(CarControlData));
  Wire.readBytes(arr,sizeof(CarControlData));
  CarControlData *data=(CarControlData*)arr;
  _manager->bindData(data);
  ModelsLogger::log(data);
  delete data;
}

void request(){
  CarSensorData *result=_manager->getData();
  char *dataAddr=(char *)(result);
  Wire.write(dataAddr,sizeof(CarSensorData));
  ModelsLogger::log(result);
  delete result;
}