#include <Arduino.h>
#include<manager/carmanager.h>
CarManager manager;
void setup() {
  Serial.begin(115200);
  manager.start();
}

void loop() {
  manager.control();
}