#include <Arduino.h>
#include<manager/carmanager.h>
#include<EEPROM.h>
CarManager manager;
void setup() {
     manager.start();
}

void loop() { 
     manager.control();
}