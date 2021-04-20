#include <Arduino.h>
#include<manager/carmanager.h>
#include<EEPROM.h>
CarManager manager;
void setup() {
     manager.start();
     pinMode(2,OUTPUT);
}

void loop() { 
     manager.control();
}