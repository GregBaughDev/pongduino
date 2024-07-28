#ifndef GAME_AREA_H
#define GAME_AREA_H
#include "paddle.h"
#include "ball.h"
#include "score.h"
#include "../controller/arduino.h"
#include "raylib.h"
#include <cstdlib>

class GameArea
{
public:
    GameArea()
        : ball(Ball(width / 2.0, height / 2.0)),
          //   l_paddle(Paddle(Keyboard(KEY_E, KEY_X), 40)),
          //   r_paddle(Paddle(Keyboard(KEY_UP, KEY_DOWN), width - 60)),
          l_paddle(Paddle(Arduino('4', '3', serialValue), 40)),
          r_paddle(Paddle(Arduino('2', '1', serialValue), width - 60)),
          score(Score()), serialValue((char *)malloc(1)) {};
    void loop();
    static const int height = 600;
    static const int width = 800;
    char *getSerialValuePtr();

private:
    void handlePaddles();
    void checkAndPublishCollision();
    void checkIsOut();
    Ball ball;
    Paddle l_paddle;
    Paddle r_paddle;
    Score score;
    char *serialValue;
};

#endif
