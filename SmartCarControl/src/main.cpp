#include <Arduino.h>
#include <carmanager.h>
CarManager * manager;
void setup() {
  manager= new CarManager();
}

void loop() {
  manager->loop();
}