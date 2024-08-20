#ifndef PONG_H
#define PONG_H
#include "gameArea.h"
#include "../multiplayer/communication.h"
#include <string>
#include <thread>

class Pong
{
public:
    Pong(
        std::string thisPort,
        std::string theirPort,
        PlayerPaddle playerPos)
        : gameArea(playerPos),
          thisData(new PongComm{200, 300, 400, 500}),
          thatData(new PongComm{0, 0, 0, 0}),
          communication(new Communication(thisPort, theirPort, thisData, thatData))
    {
        std::thread server(&Communication::startServer, communication);
        server.detach();
    };
    ~Pong()
    {
        delete thisData;
        delete thatData;
        delete communication;
    }
    void setup();
    void loop();
    char *getSerialPtr();

private:
    // TO DO - come back to ball pos
    void updateCommData();
    void publishRcvData();
    GameArea gameArea;
    PongComm *thisData;
    PongComm *thatData;
    Communication *communication;
};

#endif
