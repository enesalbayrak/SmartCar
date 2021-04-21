#include"distance.h"
#include<Arduino.h>
#define MAX_DISTANCE 2000
#define MIN_DISTANCE 0
Distance::Distance(uint8_t echoPin,uint8_t trigPin)
{
    this->echoPin=echoPin;
    this->trigPin=trigPin;
    pinMode(echoPin,INPUT);
    pinMode(trigPin,OUTPUT);
}

Distance::~Distance()
{
}
uint16_t Distance::readDistance()
{
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    float duration=pulseIn(echoPin,HIGH);
    float distance=(duration*0.34)/2;
    if(distance>MAX_DISTANCE)
        return MAX_DISTANCE;
    if(distance<MIN_DISTANCE)
        return MIN_DISTANCE;
    return distance;
}