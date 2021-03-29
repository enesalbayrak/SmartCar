#ifndef LIGHTSTATUS_H
#define LIGHTSTATUS_H
enum LightStatusType{
    CLOSE=0,
    OPEN=1
};


struct LightStatus
{
    LightStatusType LeftSignal;
    LightStatusType RightSignal;
    LightStatusType HeadLight;
    LightStatusType LongHeadLight;
    LightStatusType BackLight;
    LightStatusType QuadSignal;
};

#endif