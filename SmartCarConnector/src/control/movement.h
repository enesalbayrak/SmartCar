#ifndef MOVEMENT_H
#define MOVEMENT_H
#include<motor/motor.h>

enum MovePosition:uint8_t{
    PASSIVE=0xff,
    FRONT_LEFT=0x00,
    FRONT=0x01,
    FRONT_RIGHT=0x02,
    ANTI_CLOCKWISE=0x03,
    CLOCKWISE=0x04,
    BACK_LEFT=0x05,
    BACK=0x06,
    BACK_RIGHT=0x07
};

class Movement
{
private:
    Motor *left;
    Motor *right;
public:
    Movement();
    ~Movement();
    void move(MovePosition position);
};



#endif