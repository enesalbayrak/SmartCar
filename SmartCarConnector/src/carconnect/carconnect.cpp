#include "carconnect.h"
#include <Wire.h>
#include <Arduino.h>
#define I2C_CAR_CONNECTION_ADDRESS 41
CarConnect::CarConnect()
{
    Wire.begin();
}

void CarConnect::send(CarControlData *data){
  char *dataAddr=(char*)(data);
  Wire.beginTransmission(I2C_CAR_CONNECTION_ADDRESS); // transmit to device #4
  Wire.write(dataAddr,sizeof(CarControlData));
  Wire.endTransmission();
}

CarSensorData *CarConnect::receive(){
  Wire.requestFrom(I2C_CAR_CONNECTION_ADDRESS,sizeof(CarSensorData));
  uint8_t *resultBytes=(uint8_t *)malloc(sizeof(CarSensorData));
  Wire.readBytes(resultBytes,sizeof(CarSensorData));
  CarSensorData *result=(CarSensorData*)resultBytes;
  return result;
}
