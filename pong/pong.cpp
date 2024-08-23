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
        publishRcvData();

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
    // current state - now need to
    // sort out the weird issue when the paddle gets to the top of the screen
    // do the ball server
    // stop the servers more gracefully
    gameArea.getOtherPaddle()->setPaddle(thatData->paddlePosX, thatData->paddlePosY);
}

// ball server plan
// will be running it's own version of the game without a gui
// will use the position of the paddles for the game play
// publish out the ball position in the existing struct
// will create a ballViewer class that will just display the ball
// based on position from server
