#ifndef GAMESERVER_H
#define GAMESERVER_H
#include "../assets/ball.h"
#include "./communication.h"
#include <string>

class GameServer
{
public:
    GameServer(std::string thisPort, std::string theirPort)
        : ball(Ball(100, 200)),
          thisData(new PongComm({0, 0, 0, 0})),
          thatData(new PongComm({0, 0, 0, 0})),
          communication(new Communication(thisPort, theirPort, thisData, thatData)) {}; // hardcode the Ball constructor x and y for the min
    void loop();
    ~GameServer()
    {
        delete thisData;
        delete thatData;
        delete communication;
    };

private:
    Ball ball;
    PongComm *thisData;
    PongComm *thatData;
    Communication *communication;
};

// GameServer plan
// will be running it's own version of the game without a gui
// will use the position of the paddles for the game play
// publish out the ball position in the existing struct
// based on position from server

#endif

// TO DO

// update any initialisations with { } initialisation

// STEP ONE -> Move the ball and publish out it's position
// Consume it in one instance of the game
// COMPLETE - WE'RE GETTING THE BALL DATA, JUST SUPER FAST!
// need to slow it down to 60 fps
