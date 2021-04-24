#include "carmanager.h"
#include<Arduino.h>
#include"car/lightstatus.h"
#include <Arduino.h>
#include <definations.h>
CarManager::CarManager()
{
    carLights=new CarLighting();
    this->ldr= new Ldr(LDR_PIN);
    this->battery= new Battery(BATTERY_PIN);
    this->backDistance=new Distance(BACK_ECHO_PIN,BACK_TRIG_PIN);
    this->frontDistance=new Distance(FRONT_ECHO_PIN,FRONT_TRIG_PIN);
    this->buzzer= new BuzzerSignal(BUZZER_PIN);
    CarConnect::connect(this);
}
void CarManager::loop(){
  carLights->control();
  buzzer->control();
}

CarSensorData *CarManager::getData(){
  CarSensorData *data= new CarSensorData();
  data->batteryLevel=battery->percent();
  data->lightLevel=ldr->percent();
  data->frontDistance=frontDistance->readDistance();
  data->backDistance=backDistance->readDistance();
  return data;
}

void CarManager::bindData(CarControlData *data){
  LightStatus status;
  status.backLight=data->backLight;
  status.headLightPercent=data->headLightPercent;
  status.backHeadLight=data->backHeadLight;
  status.signalStatus=data->signalStatus;
  this->carLights->setLightStatus(status);
  this->buzzer->setLevel(data->buzzerStatus);
}