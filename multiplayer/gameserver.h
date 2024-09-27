#ifndef GAMESERVER_H
#define GAMESERVER_H
#include "server.h"
#include "../assets/ball.h"
#include "../assets/paddlevirtual.h"
#include <string>

/*
 * Upon instantiation it will start the server on a new thread and handle
 * communication with the game clients.
 *
 * This class will be running it's own version of the game and
 * will use the position of the paddles for the game play logic.
 * It publishes out the game state to both game instances and receives
 * the paddle positions of each game instance.
 */
class GameServer : private Server
{
public:
    GameServer(std::string serverPort)
        : Server{serverPort},
          ball{Ball{100, 200}},
          lPaddle{PaddleVirtual{}},
          rPaddle{PaddleVirtual{}}
    {
        std::thread gameServerThread{&GameServer::loop, this};

        serverRunThread.join();
        gameServerThread.join();
    };

private:
    void loop();
    void checkAndPublishCollision();
    void checkIsOut();
    Ball ball;
    PaddleVirtual lPaddle;
    PaddleVirtual rPaddle;
};

#endif
