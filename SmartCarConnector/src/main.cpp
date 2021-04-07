#include <Arduino.h>
#include <client/carclient.h>
#include <carconnect/carconnect.h>
#include <control/movement.h>
#define SSID  "SUPERONLINE_WiFi_3314"
#define PASSWORD  "LH7YX4LAYHHP"
#define CAR_KEY "12345678"
CarClient *client;
CarConnect *connect;
CarData *carData;
Movement *movement;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  movement= new Movement();
  client= new CarClient(SSID,PASSWORD,CAR_KEY);
  connect = new CarConnect();
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
  carData=new CarData();
  carData->backDistance=0;
  carData->batteryPower=0;
  carData->frontDistance=0;
  carData->lightLevel=0;
  
}

void loop() {
  WebData *webData=client->getData(carData);
  if(webData==nullptr)
  {
    Serial.println("Unsuccesfull");
    movement->move(MovementDirection::PASSIVE);
    return;
  }
  movement->move(webData->movementDirection);
  CarControlData *controlData= new CarControlData();
  controlData->backLight=webData->backLight;
  controlData->buzzerLevel=BuzzerSignalLevel::BUZZER_CLOSE;
  controlData->headLight=webData->headLight;
  controlData->leftSignal=webData->leftSignal;
  controlData->longHeadLight=webData->longHeadLight;
  controlData->quadSignal=webData->quadSignal;
  controlData->rightSignal=webData->rightSignal;
  delete webData;
  delay(200);
}