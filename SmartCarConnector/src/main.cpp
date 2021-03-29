#include <Arduino.h>
#include <client/carclient.h>
#define SSID  "SUPERONLINE_WiFi_3314"
#define PASSWORD  "LH7YX4LAYHHP"
#define CAR_KEY "12345678"
CarClient *client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client= new CarClient(SSID,PASSWORD,CAR_KEY);
  while (!client->connectWifi())
  {
    Serial.println("Connecting WiFi...");
  }

  while (!client->connectApi())
  {
    Serial.println("Connecting Api...");
  }
  
  
}

void loop() {
  CarData *data= new CarData();
  data->BackDistance=100;
  data->BatteryPower=55;
  data->FrontDistance=75;
  data->LightLevel=88;
  WebData *webData=client->getData(data);
  if(webData==nullptr)
  {
    Serial.println("Unsuccesfull");
    return;
  }
  Serial.print(" BackLight\t:");
  Serial.print(webData->BackLight);
  
  Serial.print(" HeadLight\t:");
  Serial.print(webData->HeadLight);
  
  Serial.print(" HornActivity\t:");
  Serial.print(webData->HornActivity);
  
  Serial.print(" LeftMotorPower\t:");
  Serial.print(webData->LeftMotorPower);
  
  Serial.print(" LeftSignal\t:");
  Serial.print(webData->LeftSignal);
  
  Serial.print(" LongHeadLight\t:");
  Serial.print(webData->LongHeadLight);
  
  Serial.print(" ParkActivity\t:");
  Serial.print(webData->ParkActivity);
  
  Serial.print(" QuadSignal\t:");
  Serial.print(webData->QuadSignal);
  
  Serial.print(" RightMotorPower\t:");
  Serial.print(webData->RightMotorPower);
  
  Serial.print(" RightSignal\t:");
  Serial.print(webData->RightSignal);
  

  delay(5000);
}