#include "carmanager.h"
#include<Arduino.h>
#define SSID  "SUPERONLINE_WiFi_3314"
#define PASSWORD  "LH7YX4LAYHHP"
#define CAR_KEY "12345678"
#define MIN_RECEIVE_MS 7000
#define LED_PIN 2
bool equalsCarControlData(CarControlData *d1,CarControlData *d2){
    return (d1->backLight==d2->backLight
         && d1->headLight==d2->headLight
         && d1->longHeadLight==d2->longHeadLight
         && d1->signalStatus==d2->signalStatus
         && d1->parkActivity==d2->parkActivity
         && d1->hornActivity==d2->hornActivity);
}

bool CarManager::carIsActive(){
  return connectData!=nullptr&&!usbMode;
}

CarManager::CarManager()
{ 
    Serial.begin(115200);
    Serial.print("\n\n\r");
    pinMode(LED_PIN,OUTPUT);
    digitalWrite(LED_PIN,HIGH);
    connectData= this->saver.read();
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
    controlData->parkActivity=false;
    controlData->hornActivity=false;
    controlData->signalStatus=SignalStatusType::SIGNAL_CLOSE;
}

CarManager::~CarManager()
{
}

void CarManager::start(){
    carConnect->send(controlData);
    if(!carIsActive())
      return;
    if (!client->connectWifi(connectData->ssid,connectData->password))
    {
      Serial.println("Connction failed");
      Serial.println(connectData->ssid);
      Serial.println(connectData->password);
      return;
    }
    if (!client->connectApi(connectData->carKey))
    {
      Serial.println("Api Not Found");
      return;
    }
}

void  CarManager::control(){
    serialconnector->read();
    if(!carIsActive())
      return;
    
    WebData *webData=client->getData(carData);
  if(webData==nullptr)
  {
    movement->move(MovementDirection::PASSIVE);
    return;
  }
  movement->move(webData->movementDirection);
  CarControlData *newControlData= new CarControlData();
  newControlData->backLight=webData->backLight;
  newControlData->parkActivity=webData->parkActivity;
  newControlData->hornActivity=webData->hornActivity;
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
ConnectData *CarManager::getData(){
  return connectData;
}

void CarManager::dataChanged(ConnectData *data) {
  if(this->connectData!=data)
    delete this->connectData;
  this->connectData=data;
}
void CarManager::save() {
  Serial.println("OK");
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
void  CarManager::startMode()
{
  this->usbMode=true;
  digitalWrite(LED_PIN,LOW);
}
void  CarManager::restart()
{
  ESP.reset();
}