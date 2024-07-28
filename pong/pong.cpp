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

        EndDrawing();
    }

    CloseWindow();
}

char *Pong::getSerialPtr()
{
    return gameArea.getSerialValuePtr();
}
