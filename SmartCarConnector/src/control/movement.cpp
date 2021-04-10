#include"movement.h"
#include<Arduino.h>
#define LEFT_MOTOR_IN_A D5
#define LEFT_MOTOR_IN_B D6
#define RIGHT_MOTOR_IN_A D8
#define RIGHT_MOTOR_IN_B D7
#define STANDBY_PIN D4
Movement::Movement()
{
    lastDirection=MovementDirection::PASSIVE;
    left=new Motor(LEFT_MOTOR_IN_A,LEFT_MOTOR_IN_B);
    right=new Motor(RIGHT_MOTOR_IN_A,RIGHT_MOTOR_IN_B);
    left->stop();
    right->stop();
    pinMode(STANDBY_PIN,OUTPUT);
    digitalWrite(STANDBY_PIN,LOW);
}

Movement::~Movement()
{
    delete left;
    delete right;
}

void Movement::move(MovementDirection direction)
{
    if(direction==lastDirection)
        return;
    lastDirection=direction;

    if(direction==MovementDirection::PASSIVE){
        left->stop();
        right->stop();
        digitalWrite(STANDBY_PIN,LOW);
        return;
    }
    
    bool in2,in1,in0;
    in2=(direction&0x04)==0x04;
    in1=(direction&0x02)==0x02;
    in0=(direction&0x01)==0x01;
    bool leftActive=(in2 | in1 | in0) & (!in2 | in1 | !in0);
    bool leftDir=!in2 & !in0 | !in1;
    bool rightActive=!in1 | (!in2 & in0) | (in2 & !in0);
    bool rightDir=!in2;

    digitalWrite(STANDBY_PIN,HIGH);
    if(leftActive)
        left->go(leftDir);
    else
        left->stop();
    
    if(rightActive)
        right->go(rightDir);
    else
        right->stop();
}