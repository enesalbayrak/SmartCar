#include <Arduino.h>
#include<manager/carmanager.h>
 CarManager manager;
void setup() {
   manager.start();
}

void loop() {
   manager.control();
}