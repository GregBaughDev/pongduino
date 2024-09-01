#include "gameArea.h"
#include <iostream>
#include <raylib.h>

void GameArea::loop()
{
    DrawLine(GameArea::width / 2, 0, GameArea::width / 2.0, GameArea::height, RAYWHITE);
    handlePaddles();
    ball.loop();
    checkAndPublishCollision();
    checkIsOut();
    score.displayScore();
}

void GameArea::handlePaddles()
{
    lPaddle.loop();
    rPaddle.loop();
}

void GameArea::checkAndPublishCollision()
{
    // if (
    //     CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, lPaddle.getRectangle()))
    // {
    //     ball.receiveHit(ball.getCircle().y - lPaddle.getRectangle().y);
    // }

    // if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, rPaddle.getRectangle()))
    // {
    //     ball.receiveHit(ball.getCircle().y - rPaddle.getRectangle().y);
    // }
}

void GameArea::checkIsOut()
{
    // if (ball.getCircle().x <= 0 || ball.getCircle().x >= width)
    // {
    //     ball.setIsStop();
    // }
}

char *GameArea::getSerialValuePtr()
{
    return serialValue;
}

Paddle *GameArea::getPaddle()
{
    switch (paddlePos)
    {
    case L:
        return &lPaddle;
        break;
    case R:
        return &rPaddle;
        break;
    }
}

Paddle *GameArea::getOtherPaddle()
{
    switch (paddlePos)
    {
    case L:
        return &rPaddle;
        break;
    case R:
        return &lPaddle;
        break;
    }
}

void GameArea::setBallView(int newX, int newY)
{
    ball.setCircle(newX, newY);
}
