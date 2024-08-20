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
        updateCommData();
        communication->clientSend();

        EndDrawing();
    }

    CloseWindow();
}

char *Pong::getSerialPtr()
{
    return gameArea.getSerialValuePtr();
}

void Pong::updateCommData()
{
    thisData->paddlePosX = gameArea.getPaddle()->getRectangle().x;
    thisData->paddlePosY = gameArea.getPaddle()->getRectangle().y;
}

void Pong::publishRcvData()
{
    // current state
    // this isn't working - thoughts, it could be to do with passing the pointer over the thread
    // would be good to confirm thatData is receiving the data
    // also need to update the paddles so we can only control one
    gameArea.getOtherPaddle()->setPaddle(thatData->paddlePosX, thatData->paddlePosY);
}
