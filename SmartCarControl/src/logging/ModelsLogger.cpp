#include "ModelsLogger.h"
#include <Arduino.h>
ModelsLogger::ModelsLogger()
{
}

void ModelsLogger::log(CarControlData * data){
    Serial.println("***************LIGHT DATA***************");
    Serial.print("backLight \t:");
    Serial.println(data->backLight);
    Serial.print("headLight \t:");
    Serial.println(data->headLight);  
    Serial.print("longHeadLight \t:");
    Serial.println(data->longHeadLight);
    Serial.print("signalStatus \t:");
    Serial.println(data->signalStatus);  
    Serial.print("parkActivity \t:");
    Serial.println(data->parkActivity);  
    Serial.print("hornActivity \t:");
    Serial.println(data->hornActivity);  
    Serial.println("**********LIGHT DATA END****************");
}

void ModelsLogger::log(CarSensorData * data){
    Serial.println("***************SENSOR DATA**************");
    Serial.print("lightLevel \t:");
    Serial.print(data->lightLevel);
    Serial.print(" batteryLevel \t:");
    Serial.println(data->batteryLevel);  
    Serial.print("frontDistance \t:");
    Serial.print(data->frontDistance);
    Serial.print(" backDistance \t:");
    Serial.println(data->backDistance);  
    Serial.println("*************SENSOR DATA END************");
}