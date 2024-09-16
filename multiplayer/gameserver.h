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
    GameServer(std::string serverPort)
        : ball(Ball(100, 200)),
          lPaddle(PaddleVirtual()), // Do we need this?
          rPaddle(PaddleVirtual()),
          Server(serverPort)
    {
        std::thread gameServerThread(&GameServer::loop, this);

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

// GameServer plan USE THIS AS MAIN NOTES AREA!
// will be running it's own version of the game without a gui
// will use the position of the paddles for the game play
// publish out the ball position in the existing struct
// based on position from server

#endif

// Current state
// The direction of data flows is super wacky
// need to also do a health check to confirm server is running when starting a pong game
// update any initialisations with { } initialisation
// replace new and delete with stack pointers
// or do it all with shared pointers - come back to this
// add documentation
