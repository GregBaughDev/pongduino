#ifndef GAME_AREA_H
#define GAME_AREA_H
#include "paddle.h"
#include "ball.h"
#include "raylib.h"

class GameArea
{
public:
    GameArea()
        : width(800),
          height(600),
          ball(Ball(width / 2, height / 2)),
          l_paddle(Paddle(Keyboard(KEY_E, KEY_X), 20, ball)),
          r_paddle(Paddle(Keyboard(KEY_UP, KEY_DOWN), width - 40, ball)){};
    // Will have score in constructor
    void setup();
    void loop();
    const int width;
    const int height;

private:
    void handlePaddles();
    Ball ball;
    Paddle l_paddle;
    Paddle r_paddle;
};

#endif
