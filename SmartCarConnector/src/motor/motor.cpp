#include "motor.h"
#include "Arduino.h"
void high(uint8_t pin){
    digitalWrite(pin,HIGH);
}
void low(uint8_t pin){
    digitalWrite(pin,LOW);
}
Motor::Motor(uint8_t motorA,uint8_t motorB)
{
    this->motorA=motorA;
    this->motorB=motorB;
    pinMode(motorA,OUTPUT);
    pinMode(motorB,OUTPUT);
}
void Motor::forward(){
    high(motorA);
    low(motorB);
}

void Motor::back(){
    high(motorB);
    low(motorA);
}

void Motor::go(bool isForward){
    isForward?forward():back();
}

void Motor::stop(){
    low(motorA);
    low(motorB);
}
Motor::~Motor()
{
    stop();
}