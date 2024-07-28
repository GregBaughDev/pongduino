#ifndef PONG_H
#define PONG_H
#include "gameArea.h"

class Pong
{
public:
    Pong() : gameArea() {};
    void setup();
    void loop();
    char *getSerialPtr();

private:
    GameArea gameArea;
};

#endif
