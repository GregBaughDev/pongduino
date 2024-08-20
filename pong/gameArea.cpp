#include "gameArea.h"
#include <iostream>
#include <raylib.h>

void GameArea::loop()
{
    DrawLine(GameArea::width / 2, 0, GameArea::width / 2.0, GameArea::height, RAYWHITE);
    handlePaddles();
    // ball.handleBall();
    checkAndPublishCollision();
    checkIsOut();
    score.displayScore();
}

void GameArea::handlePaddles()
{
    l_paddle.loop();
    r_paddle.loop();
}

void GameArea::checkAndPublishCollision()
{
    if (
        CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, l_paddle.getRectangle()))
    {
        ball.receiveHit(ball.getCircle().y - l_paddle.getRectangle().y);
    }

    if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, r_paddle.getRectangle()))
    {
        ball.receiveHit(ball.getCircle().y - r_paddle.getRectangle().y);
    }
}

void GameArea::checkIsOut()
{
    if (ball.getCircle().x <= 0 || ball.getCircle().x >= width)
    {
        ball.setIsStop();
    }
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
        return &l_paddle;
        break;
    case R:
        return &r_paddle;
        break;
    }
}

Paddle *GameArea::getOtherPaddle()
{
    switch (paddlePos)
    {
    case L:
        return &r_paddle;
        break;
    case R:
        return &l_paddle;
        break;
    }
}
