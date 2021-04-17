#include "carmanager.h"
#include<Arduino.h>
#define SSID  "SUPERONLINE_WiFi_3314"
#define PASSWORD  "LH7YX4LAYHHP"
#define CAR_KEY "12345678"
#define MIN_RECEIVE_MS 7000
bool equalsCarControlData(CarControlData *d1,CarControlData *d2){
    return (d1->backLight==d2->backLight
         && d1->headLight==d2->headLight
         && d1->longHeadLight==d2->longHeadLight
         && d1->signalStatus==d2->signalStatus
         && d1->buzzerLevel==d2->buzzerLevel);
}

CarManager::CarManager()
{
    movement= new Movement();
    client= new CarClient(SSID,PASSWORD,CAR_KEY);
    connect = new CarConnect();
    carData=new CarData();
    carData->backDistance=0;
    carData->batteryPower=0;
    carData->frontDistance=0;
    carData->lightLevel=0;
    controlData= new CarControlData();
    controlData->backLight=LightStatusType::LIGHT_CLOSE;
    controlData->headLight=LightStatusType::LIGHT_CLOSE;
    controlData->longHeadLight=LightStatusType::LIGHT_CLOSE;
    controlData->buzzerLevel=BuzzerSignalLevel::BUZZER_CLOSE;
    controlData->signalStatus=SignalStatusType::SIGNAL_CLOSE;
}

CarManager::~CarManager()
{
}

void CarManager::start(){
    lastMillis=millis();
    Serial.println();
    while (!client->connectWifi())
    {
        Serial.println("Connecting WiFi...");
    }

    while (!client->connectApi())
    {
        Serial.println("Connecting Api...");
    }
    Serial.println("Connections Completed!");
    connect->send(controlData);
}

void  CarManager::control(){
    WebData *webData=client->getData(carData);
  if(webData==nullptr)
  {
    Serial.println("Unsuccesfull");
    movement->move(MovementDirection::PASSIVE);
    return;
  }
  movement->move(webData->movementDirection);
  CarControlData *newControlData= new CarControlData();
  newControlData->backLight=webData->backLight;
  newControlData->buzzerLevel=BuzzerSignalLevel::BUZZER_CLOSE;
  newControlData->headLight=webData->headLight;
  newControlData->longHeadLight=webData->longHeadLight;
  newControlData->signalStatus=webData->signalStatus;
  if(!equalsCarControlData(controlData,newControlData))
  {
    connect->send(newControlData);
    delete controlData;
    controlData=newControlData;
  }
  else
  {
    delete newControlData;
  }
  receiveSensorData();
  delete webData;
}
void CarManager::receiveSensorData(){
    long ms=millis();
    if(ms-lastMillis<MIN_RECEIVE_MS)
        return;
    lastMillis=ms;
    CarSensorData *sensorData= connect->receive();
    carData->backDistance=sensorData->backDistance;
    carData->frontDistance=sensorData->frontDistance;
    carData->batteryPower=sensorData->batteryLevel;
    carData->lightLevel=sensorData->lightLevel;
}
