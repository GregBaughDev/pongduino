#ifndef PONG_H
#define PONG_H
#include "gameArea.h"

// maybe keep the PongDataStruct here?
struct
{
    int ballPosX;
    int ballPosY;
    int paddlePosX;
    int paddlePosY;
} typedef PongComm;

class Pong
{
public:
    Pong() : gameArea(),
             thisData({200, 300, 400, 500}),
             thatData({0, 0, 0, 0}) {};
    void setup();
    void loop();
    char *getSerialPtr();

private:
    GameArea gameArea;
    PongComm thisData;
    PongComm thatData;
};

#endif
