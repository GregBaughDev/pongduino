#ifndef GAME_AREA_H
#define GAME_AREA_H
#include "../assets/paddle.h"
#include "../assets/paddleview.h"
#include "../assets/ballview.h"
#include "score.h"
#include "../controller/arduino.h"
#include "../controller/keyboard.h"
#include "raylib.h"
#include <cstdlib>

enum PlayerPaddle
{
    L,
    R
};
class GameArea
{
public:
    GameArea(PlayerPaddle playerPaddle)
        : ball{BallView{}},
          serialValue{0},
          // thisPaddle{Paddle{new Keyboard{KEY_E, KEY_X}, 40}},
          thisPaddle{Paddle{new Keyboard{KEY_UP, KEY_DOWN}, width - 60}},
          otherPaddle{PaddleView{}},
          //   l_paddle{Paddle{new Arduino{'4', '3', &serialValue}, 40}},
          //   r_paddle{Paddle{new Arduino{'2', '1', &serialValue}, width - 60}},
          score{Score{}},
          paddlePos{playerPaddle} {};
    void loop();
    static const int height = 600;
    static const int width = 800;
    char *getSerialValuePtr();
    Paddle *getPaddle();
    void setOtherPaddle(float newXPos, float newYPos);
    void setBallView(int newX, int newY);

private:
    void handlePaddles();
    BallView ball;
    char serialValue;
    Paddle thisPaddle;
    PaddleView otherPaddle;
    Score score;
    PlayerPaddle paddlePos;
};

#endif
