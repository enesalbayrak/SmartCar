#include "carconnect.h"
#include <Wire.h>
#include <Arduino.h>
#define I2C_CAR_CONNECTION_ADDRESS 41
CarConnect::CarConnect()
{
    Wire.begin();
}

CarSensorData *CarConnect::communicate(CarControlData *data){
  char *dataAddr=(char*)(data);
  Wire.beginTransmission(I2C_CAR_CONNECTION_ADDRESS); // transmit to device #4
  Wire.write(dataAddr,sizeof(CarControlData));
  int res=Wire.endTransmission();
  Serial.print("Transmission Status:");
  Serial.println(res);
  Wire.requestFrom(I2C_CAR_CONNECTION_ADDRESS,sizeof(CarSensorData));
  uint8_t *resultBytes=(uint8_t *)malloc(sizeof(CarSensorData));
  Wire.readBytes(resultBytes,sizeof(CarSensorData));
  CarSensorData *result=(CarSensorData*)resultBytes;
  Serial.print("BatteryLevel:");
  Serial.print(result->batteryLevel);
  Serial.print(" LightLevel:");
  Serial.println(result->lightLevel);
  delay(1000);
  return result;
}