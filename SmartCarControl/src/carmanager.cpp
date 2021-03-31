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
  data->BatteryLevel=93;
  data->LightLevel=75;
  return data;
}

void CarManager::bindData(CarControlData *data){
  LightStatus status;
  status.BackLight=data->BackLight;
  status.HeadLight=data->HeadLight;
  Serial.print("LSS");
  Serial.println(data->LeftSignal);
  Serial.print("RSS");
  Serial.println(data->RightSignal);

  status.LeftSignal=data->LeftSignal;
  status.RightSignal=data->RightSignal;
  status.QuadSignal=data->QuadSignal;
  status.LongHeadLight=data->LongHeadLight;
  this->carLights->setLightStatus(status);
  Serial.print("LeftSignal:\t ");
  Serial.print(data->LeftSignal);
  Serial.print("\t RightSignal:\t ");
  Serial.print(data->RightSignal);
  Serial.print("\t QuadSignal:\t ");
  Serial.print(data->QuadSignal);
  Serial.print("\t LeftMotorPower:\t ");
  Serial.print(data->LeftMotorPower);
  Serial.print("\t RightMotorPower:\t ");
  Serial.print(data->RightMotorPower);
  Serial.print("\t HeadLight:\t ");
  Serial.print(data->HeadLight);
  Serial.print("\t LongHeadLight:\t ");
  Serial.print(data->LongHeadLight);
  Serial.print("\t BackLight:\t ");
  Serial.print(data->BackLight);
  Serial.print("\t BuzzerLevel:\t ");
  Serial.print(data->BuzzerLevel);
  Serial.println();
}