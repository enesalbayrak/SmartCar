 #include "carclient.h"
#include <esp8266wifi.h>
#include <esp8266httpclient.h>
#include <ArduinoJson.h>
#define CAR_API_ENDPOINT "http://192.168.1.26:5000/api/car"

 CarClient::CarClient(char * ssid,char *password,char *key){
     this->ssid=ssid;
     this->password=password;
     this->key=key;
}

bool  CarClient::connectWifi(){
    WiFi.begin(ssid, password);
    uint8_t count=0;
    while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
     if(count==10)
      return false;
      count++;
    }
    return true;
}

bool  CarClient::connectApi(){
    if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;  
    http.begin(String(CAR_API_ENDPOINT)); 
    http.addHeader("connection-key",key);
    int httpCode = http.GET(); 
    if (httpCode > 0) { 
      return true;
    }
    http.end();
  }
  return false;
}

WebData * CarClient::getData(CarData *carData){
   if (WiFi.status() == WL_CONNECTED) { 
    DynamicJsonDocument doc(1024);
    doc["ll"]=carData->LightLevel;
    doc["bp"]=carData->BatteryPower;
    doc["bd"]=carData->BackDistance;
    doc["fd"]=carData->FrontDistance;
    HTTPClient http; 
    http.begin(String(CAR_API_ENDPOINT)); 
    http.addHeader("connection-key",key);
    http.addHeader("Content-Type","application/json");
    char json[1024];
    serializeJson(doc,json,1024);
    int httpCode = http.POST(json); 
    if (httpCode > 0) {
      String payload = http.getString();   
      deserializeJson(doc,payload);
      WebData * wd= new WebData();
      wd->LeftMotorPower=doc["lmp"];
      wd->RightMotorPower=doc["rmp"];
      wd->HeadLight=doc["hl"];
      wd->BackLight=doc["bl"];
      wd->LeftSignal=doc["ls"];
      wd->RightSignal=doc["rs"];
      wd->LongHeadLight=doc["lhl"];
      wd->QuadSignal=doc["qs"];
      wd->ParkActivity=doc["prk"];
      wd->HornActivity=doc["hrn"];
      return wd;
    }
    http.end();
 
  }
  return nullptr;
}