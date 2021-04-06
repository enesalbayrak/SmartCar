#ifndef MOVEMENTLOGGER_H
#define MOVEMENTLOGGER_H
class MovementLogger
{
private:
    MovementLogger();
    ~MovementLogger();
public:
    static void inLogger(bool in0,bool in1,bool in2);
    static void motorLogger(bool leftActive,bool leftDir,bool rightActive,bool rightDir);
};

#endif