#include <Arduino.h>
#include <client/carclient.h>
#include <carconnect/carconnect.h>
#define SSID  "SUPERONLINE_WiFi_3314"
#define PASSWORD  "LH7YX4LAYHHP"
#define CAR_KEY "12345678"
CarClient *client;
CarConnect *connect;
CarData *carData;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client= new CarClient(SSID,PASSWORD,CAR_KEY);
  connect = new CarConnect();
  while (!client->connectWifi())
  {
    Serial.println("Connecting WiFi...");
  }

  while (!client->connectApi())
  {
    Serial.println("Connecting Api...");
  }
  carData=new CarData();
  carData->BackDistance=0;
  carData->BatteryPower=0;
  carData->FrontDistance=0;
  carData->LightLevel=0;
  
}

void loop() {
  WebData *webData=client->getData(carData);
  if(webData==nullptr)
  {
    Serial.println("Unsuccesfull");
    return;
  }
  Serial.println("Data Sending...");

  CarControlData *controlData= new CarControlData();
  controlData->BackLight=webData->BackLight;
  controlData->BuzzerLevel=BuzzerSignalLevel::BUZZER_CLOSE;
  controlData->HeadLight=webData->HeadLight;
  controlData->LeftMotorPower=webData->LeftMotorPower;
  controlData->LeftSignal=webData->LeftSignal;
  controlData->LongHeadLight=webData->LongHeadLight;
  controlData->QuadSignal=webData->QuadSignal;
  controlData->RightMotorPower=webData->RightMotorPower;
  controlData->RightSignal=webData->RightSignal;
  CarSensorData * sensorData=connect->communicate(controlData);
  carData->BatteryPower=sensorData->BatteryLevel;
  carData->LightLevel=sensorData->LightLevel;
  delay(5000);
}