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
    connectData= new ConnectData;
    connectData->carKey=CAR_KEY;
    connectData->ssid=SSID;
    connectData->password=PASSWORD;
    this->serialconnector= new SerialDataConnector(this);
    movement= new Movement();
    client= new CarClient();
    carConnect = new CarConnect();
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

  Serial.begin(115200);
    Serial.println();
    if(!Serial)
    {

      while (!client->connectWifi(connectData->ssid,connectData->password))
      {
          Serial.println("Connecting WiFi...");
      }
      while (!client->connectApi(connectData->carKey))
      {
          Serial.println("Connecting Api...");
      }
      Serial.println("Connections Completed!");
      carConnect->send(controlData);
    }
}

void  CarManager::control(){
    serialconnector->read();
    if(Serial)
      return;
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
    carConnect->send(newControlData);
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
    CarSensorData *sensorData= carConnect->receive();
    carData->backDistance=sensorData->backDistance;
    carData->frontDistance=sensorData->frontDistance;
    carData->batteryPower=sensorData->batteryLevel;
    carData->lightLevel=sensorData->lightLevel;
}
ConnectData CarManager::getData(){
  return *connectData;
}

void CarManager::dataChanged(ConnectData data) {
  this->connectData->carKey=data.carKey;
  this->connectData->ssid=data.ssid;
  this->connectData->password=data.password;
}
void CarManager::save() {

}
void CarManager::connect() {
    if(client->connectWifi(connectData->ssid,connectData->password))
    {
      Serial.print("Connection successful");
    }
    else
    {
      Serial.print("Connection unsuccessful");
    }
    
    Serial.print("\t SSID:");
    Serial.println(connectData->ssid);
}
void  CarManager::exit(){

}