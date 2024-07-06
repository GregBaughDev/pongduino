#include "gameArea.h"
#include <iostream>

void GameArea::loop()
{
    handlePaddles();
    ball.handleBall();
}

void GameArea::setup()
{
    // not implemented
    std::cout << "Set up tasks\n";
}

void GameArea::handlePaddles()
{
    l_paddle.loop();
    r_paddle.loop();
}
