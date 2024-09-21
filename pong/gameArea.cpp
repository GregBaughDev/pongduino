#include "gamearea.h"
#include <iostream>
#include <raylib.h>

void GameArea::loop()
{
    DrawLine(GameArea::width / 2, 0, GameArea::width / 2.0, GameArea::height, RAYWHITE);
    handlePaddles();
    ball.loop();
    score.displayScore(); // TODO - Come back to this and send the score
}

void GameArea::handlePaddles()
{
    thisPaddle.loop();
    otherPaddle.loop();
}

char *GameArea::getSerialValuePtr()
{
    return &serialValue;
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
