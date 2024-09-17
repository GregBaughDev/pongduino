#ifndef PONG_H
#define PONG_H
#include "gamearea.h"
#include "../multiplayer/client.h"
#include <string>
#include <thread>

class Pong
{
public:
    Pong(
        std::string serverPort,
        PlayerPaddle playerPos)
        : gameArea(GameArea(playerPos)),
          playerPos(playerPos),
          gameData(PongComm{0, 0, 0, 0}),
          paddleData(PaddleComm{playerPos, 0, 0}),
          client(Client(serverPort, &gameData, &paddleData))
    {
        setup();
    };
    void loop();
    char *getSerialPtr();

private:
    void setup();
    void updatePaddleData();
    void receiveGameData();
    PlayerPaddle playerPos;
    GameArea gameArea;
    PongComm gameData;
    PaddleComm paddleData;
    Client client;
};

#endif
