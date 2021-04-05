#include"movement.h"
#include<Arduino.h>
#define LEFT_MOTOR_IN_A D5
#define LEFT_MOTOR_IN_B D6
#define RIGHT_MOTOR_IN_A D8
#define RIGHT_MOTOR_IN_B D7
Movement::Movement()
{
    left=new Motor(LEFT_MOTOR_IN_A,LEFT_MOTOR_IN_B);
    right=new Motor(RIGHT_MOTOR_IN_A,RIGHT_MOTOR_IN_B);
}

Movement::~Movement()
{
    delete left;
    delete right;
}

void Movement::move(MovePosition position)
{
    if(position==MovePosition::PASSIVE){
        left->stop();
        right->stop();
        return;
    }
    bool in2,in1,in0;
    in2=(position&0x04)==0x04;
    in1=(position&0x02)==0x02;
    in0=(position&0x01)==0x01;
    bool leftActive=(in2 | in1 | in0) & (!in2 | in1 | !in0);
    bool leftDir=!in2 & !in0 | !in1;
    bool rightActive=!in1 | (!in2 & in0) | (in2 & !in0);
    bool rightDir=!in2;
    // String printText="in data:";
    // printText+=in2?"1":"0";
    // printText+=in1?"1":"0";
    // printText+=in0?"1":"0";
    // //Serial.println(printText);

    // printText="move data";
    
    // printText+="\tleft active:";
    // printText+=leftActive?"1":"0";
    // printText+="\tleft:";
    // printText+=leftDir?"1":"0";
    // Serial.print(printText);
    // printText="";
    // printText+="\tright active:";
    // printText+=rightActive?"1":"0";
    // printText+="\tright:";
    // printText+=rightDir?"1":"0";

    // Serial.println(printText);

    if(leftActive)
        left->go(leftDir);
    else
        left->stop();
    
    if(rightActive)
        right->go(rightDir);
    else
        right->stop();
}