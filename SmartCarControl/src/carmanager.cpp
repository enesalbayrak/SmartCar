#include "carmanager.h"
#include<Arduino.h>
#include"car/lightstatus.h"
CarManager::CarManager()
{
    carLights=new CarLighting();
    Serial.begin(9600);
    Serial.println("Serial Started");
    CarConnect::connect(this);
}
void CarManager::loop(){
  carLights->control();
}

CarSensorData *CarManager::getData(){
  CarSensorData *data= new CarSensorData();
  data->batteryLevel=93;
  data->lightLevel=75;
  return data;
}

void CarManager::bindData(CarControlData *data){
  LightStatus status;
  status.BackLight=data->backLight;
  status.HeadLight=data->headLight;
  status.SignalStatus=data->signalStatus;
  status.LongHeadLight=data->longHeadLight;

  this->carLights->setLightStatus(status);
}