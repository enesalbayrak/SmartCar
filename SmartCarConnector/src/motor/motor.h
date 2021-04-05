#ifndef __MOTOR_H__
#define __MOTOR_H__
#include<stdint.h>
class Motor
{
private:
    /* data */
public:
    Motor(uint8_t motorA,uint8_t motorB);
    ~Motor();
    void forward();
    void back();
    void go(bool isForward);
    void stop();
private:
    uint8_t motorA;
    uint8_t motorB;
};


#endif