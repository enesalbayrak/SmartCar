#include "carmanager.h"
#include<Arduino.h>
#include"car/lightstatus.h"
#include <Arduino.h>
#define LDR_PIN A0
#define BATTERY_PIN A1
CarManager::CarManager()
{
    carLights=new CarLighting();
    this->ldr= new Ldr(LDR_PIN);
    this->battery= new Battery(BATTERY_PIN);
    CarConnect::connect(this);
}
void CarManager::loop(){
  carLights->control();
}

CarSensorData *CarManager::getData(){
  CarSensorData *data= new CarSensorData();
  data->batteryLevel=battery->percent();
  data->lightLevel=ldr->percent();
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