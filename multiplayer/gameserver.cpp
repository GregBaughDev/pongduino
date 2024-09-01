#include "gameserver.h"
#include <iostream>
#include <thread>

void GameServer::loop()
{
    while (true)
    { // TODO should this be while !SIGTERM or something like that?
        ball.handleBall();

        thisData->ballPosX = ball.getCircle().x;
        thisData->ballPosY = ball.getCircle().y;

        communication->clientSend();

        std::cout << "BALLPOSX IS " << ball.getCircle().x << " ,BALLPOSY IS " << ball.getCircle().y << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
