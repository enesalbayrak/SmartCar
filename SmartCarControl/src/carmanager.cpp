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
    this->voiceManager= new VoiceManager(BUZZER_PIN);
    CarConnect::connect(this);
}
void CarManager::loop(){
  carLights->control();
  if(voiceManager->getParkActivity())
  voiceManager->set(backDistance->readDistance(),frontDistance->readDistance());
  voiceManager->control();
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
  status.BackLight=data->backLight;
  status.HeadLight=data->headLight;
  status.SignalStatus=data->signalStatus;
  status.LongHeadLight=data->longHeadLight;
  this->carLights->setLightStatus(status);
  this->voiceManager->set(data->parkActivity,data->hornActivity, backDistance->readDistance(),frontDistance->readDistance());
}