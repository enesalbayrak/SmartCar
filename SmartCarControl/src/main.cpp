#include <Arduino.h>
#include <carmanager.h>
CarManager * manager;
uint16_t x=900;
long lastMs=millis();
void setup() {
  Serial.begin(9600);
   manager= new CarManager();
}
void loop() {
   manager->loop();
}