#include "pong.h"
#include "gameArea.h"
#include <raylib.h>

void Pong::setup()
{
    InitWindow(gameArea.width, gameArea.height, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    gameArea.setup();
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
