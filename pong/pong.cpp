#include "pong.h"
#include "gameArea.h"
#include <raylib.h>

void Pong::setup()
{
    InitWindow(gameArea.width, gameArea.height, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
}

void Pong::loop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        gameArea.loop();
        updatePaddleData();
        client->send();
        receiveGameData();

        EndDrawing();
    }

    CloseWindow();
}

char *Pong::getSerialPtr()
{
    return gameArea.getSerialValuePtr();
}

void Pong::updatePaddleData()
{
    paddleData->paddlePosX = gameArea.getPaddle()->getRectangle().x;
    paddleData->paddlePosY = gameArea.getPaddle()->getRectangle().y;
}

void Pong::receiveGameData()
{
    if (playerPos == L)
    {
        gameArea.setOtherPaddle(gameData->rPaddlePosX, gameData->rPaddlePosY);
    }
    else
    {
        gameArea.setOtherPaddle(gameData->lPaddlePosX, gameData->lPaddlePosY);
    }
    gameArea.setBallView(gameData->ballPosX, gameData->ballPosY);
}
