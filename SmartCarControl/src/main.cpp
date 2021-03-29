#include <Arduino.h>
#include <car/carlighting.h>
CarLighting *carLights;
void setup() {
    carLights= new CarLighting();
    
  LightStatus status;
  status.BackLight=LightStatusType::OPEN;
  status.HeadLight=LightStatusType::OPEN;
  status.LeftSignal=LightStatusType::CLOSE;
  status.RightSignal=LightStatusType::OPEN;
  status.QuadSignal=LightStatusType::OPEN;
  carLights->setLightStatus(status);
}

void loop() {
  carLights->control();
}