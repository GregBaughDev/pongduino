#ifndef PONG_H
#define PONG_H
#include "gamearea.h"
#include "../multiplayer/client.h"
#include <string>
#include <thread>
#include <memory>

class Pong
{
public:
    Pong(
        std::string serverPort,
        PlayerPaddle playerPos)
        : gameArea{GameArea{playerPos}},
          playerPos{playerPos},
          gameData{std::make_unique<PongComm>(PongComm{0, 0, 0, 0})},
          paddleData{std::make_unique<PaddleComm>(PaddleComm{playerPos, 0, 0})},
          client{Client{serverPort, gameData.get(), paddleData.get()}}
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
    std::unique_ptr<PongComm> gameData;
    std::unique_ptr<PaddleComm> paddleData;
    Client client;
};

#endif
