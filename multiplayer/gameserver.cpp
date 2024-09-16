#include "gameserver.h"
#include "../pong/gamearea.h"
#include <iostream>
#include <thread>

void GameServer::loop()
{
    std::cout << "Starting game loop...\n";

    while (true)
    { // TODO should this be while !SIGTERM or something like that?
        ball.handleBall();
        checkAndPublishCollision();
        checkIsOut();

        Server::gameState->ballPosX = ball.getCircle().x;
        Server::gameState->ballPosY = ball.getCircle().y;

        lPaddle.setRectangle(Server::gameState->lPaddlePosX, Server::gameState->lPaddlePosY);
        rPaddle.setRectangle(Server::gameState->rPaddlePosX, Server::rPaddleState->paddlePosY);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void GameServer::checkAndPublishCollision()
{
    if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, lPaddle.getRectangle()))
    {
        ball.receiveHit(ball.getCircle().y - lPaddle.getRectangle().y);
    }

    if (CheckCollisionCircleRec(ball.getCircle(), ball.getRadius() + 1, rPaddle.getRectangle()))
    {
        ball.receiveHit(ball.getCircle().y - rPaddle.getRectangle().y);
    }
}

void GameServer::checkIsOut()
{
    if (ball.getCircle().x <= 0 || ball.getCircle().x >= GameArea::width)
    {
        ball.setIsStop();
    }
}
