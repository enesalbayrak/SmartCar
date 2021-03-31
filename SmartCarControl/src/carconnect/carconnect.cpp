#include"carconnect.h"
#include <Wire.h>
#include <stdlib.h>
#include <Arduino.h>
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
}

void request(){
  CarSensorData *result=_manager->getData();
  char *dataAddr=(char *)(result);
  Serial.print("Light \t:");
  Serial.print(result->LightLevel);
  Serial.print(" Battery \t:");
  Serial.println(result->BatteryLevel);  
  Wire.write(dataAddr,sizeof(CarSensorData));
}