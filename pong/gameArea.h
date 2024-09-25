#ifndef GAME_AREA_H
#define GAME_AREA_H
#include "score.h"
#include "../assets/paddle.h"
#include "../assets/paddleview.h"
#include "../assets/ballview.h"
#include "../controller/arduino.h"
#include "../controller/keyboard.h"
#include "raylib.h"
#include <cstdlib>

class GameArea
{
public:
    GameArea(Paddle playerPaddle)
        : ball{BallView{}},
          thisPaddle(playerPaddle),
          otherPaddle{PaddleView{}},
          score{Score{}} {};
    void loop();
    static const int height = 600;
    static const int width = 800;
    Paddle *getPaddle();
    void setOtherPaddle(float newXPos, float newYPos);
    void setBallView(int newX, int newY);

private:
    void handlePaddles();
    BallView ball;
    Paddle thisPaddle;
    PaddleView otherPaddle;
    Score score;
};

#endif
