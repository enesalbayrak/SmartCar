 #include "carclient.h"
#include <esp8266wifi.h>
#include <esp8266httpclient.h>
#include <ArduinoJson.h>
#include <logging/webdatalogger.h>
#define CAR_API_ENDPOINT "http://192.168.1.26:5000/api/car"

 CarClient::CarClient(){
}

bool  CarClient::connectWifi(String ssid,String password){
     this->ssid=ssid;
     this->password=password;
    WiFi.begin(ssid, password);
    uint8_t count=0;
    while (WiFi.status() != WL_CONNECTED) {
     delay(250);
     if(count==40)
      return false;
      count++;
    }
    return true;
}

bool  CarClient::connectApi(String key){
    this->key=key;
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
    doc["ll"]=carData->lightLevel;
    doc["bp"]=carData->batteryPower;
    doc["bd"]=carData->backDistance;
    doc["fd"]=carData->frontDistance;
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
      wd->movementDirection=doc["md"];
      wd->headLightPercent=doc["hl"];
      wd->backHeadLight=doc["bh"];
      wd->buzzerStatus=doc["bz"];
      wd->backLight=doc["bl"];
      wd->signalStatus=doc["ss"];
      // WebDataLogger::log(wd);
      return wd;
    }
    http.end();
 
  }
  return nullptr;
}