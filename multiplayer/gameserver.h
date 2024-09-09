#ifndef GAMESERVER_H
#define GAMESERVER_H
#include "../assets/ball.h"
#include "../assets/paddlevirtual.h"
#include "server.h"
#include <string>

/*
 * Upon instantiation it will start the server on a new thread and handle
 * communication with the game clients
 */
class GameServer : private Server
{
public:
    GameServer(std::string serverPort, int clientPort1, int clientPort2)
        : ball(Ball(100, 200)),
          lPaddle(), // Do we need this?
          rPaddle(),
          Server(serverPort, clientPort1, clientPort2)
    {
        std::thread gameServerThread(&GameServer::loop, this);

        serverRunThread.join();
        gameServerThread.join();
    };

private:
    Ball ball;
    PaddleVirtual lPaddle;
    PaddleVirtual rPaddle;
    void loop();
};

// GameServer plan USE THIS AS MAIN NOTES AREA!
// will be running it's own version of the game without a gui
// will use the position of the paddles for the game play
// publish out the ball position in the existing struct
// based on position from server

#endif

// Current state
// We now have the client and server classes working. Next step is to break out the
// pong and gamearea classes to be runnable in the gameserver and also for the gui versions of the
// game

// TO DO
// update any initialisations with { } initialisation
// replace new and delete with stack pointers
// or do it all with shared pointers - come back to this
