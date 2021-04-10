#ifndef MOVEMENT_H
#define MOVEMENT_H
#include<enums.h>
#include<motor/motor.h>

class Movement
{
private:
    Motor *left;
    Motor *right;
    MovementDirection lastDirection;
public:
    Movement();
    ~Movement();
    void move(MovementDirection direction);
};



#endif