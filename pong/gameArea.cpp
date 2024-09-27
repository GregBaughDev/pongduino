#include "gamearea.h"
#include <iostream>
#include <raylib.h>

void GameArea::loop()
{
    DrawLine(GameArea::width / 2, 0, GameArea::width / 2.0, GameArea::height, RAYWHITE);
    handlePaddles();
    ball.loop();
}

void GameArea::handlePaddles()
{
    thisPaddle.loop();
    otherPaddle.loop();
}

Paddle *GameArea::getPaddle()
{
    return &thisPaddle;
}

void GameArea::setOtherPaddle(float newXPos, float newYPos)
{
    otherPaddle.setRectangle(newXPos, newYPos);
}

void GameArea::setBallView(int newX, int newY)
{
    ball.setCircle(newX, newY);
}
