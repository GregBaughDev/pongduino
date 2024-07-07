#include "gameArea.h"
#include <iostream>

void GameArea::loop()
{
    handlePaddles();
    ball.handleBall();
    checkAndPublishCollision();
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

void GameArea::checkAndPublishCollision()
{
    if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius(), l_paddle.getRectangle()))
    {
        ball.receiveCollision(ball.getCircle().y - l_paddle.getRectangle().y);
    }

    if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius(), r_paddle.getRectangle()))
    {
        ball.receiveCollision(ball.getCircle().y - r_paddle.getRectangle().y);
    }
}
