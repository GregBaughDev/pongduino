#include "gameserver.h"
#include <iostream>
#include <thread>

void GameServer::loop()
{
    std::cout << "Starting game loop...\n";

    while (true)
    { // TODO should this be while !SIGTERM or something like that?
        ball.handleBall();

        Server::gameState->ballPosX = ball.getCircle().x;
        Server::gameState->ballPosY = ball.getCircle().y;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
