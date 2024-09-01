#ifndef GAME_AREA_H
#define GAME_AREA_H
#include "../assets/paddle.h"
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
        : ball(BallView()),
          serialValue((char *)malloc(1)),
          // to do - move the below to Pong
          lPaddle(Paddle(new Keyboard(KEY_E, KEY_X), 40)),
          rPaddle(Paddle(new Keyboard(KEY_UP, KEY_DOWN), width - 60)),
          //   l_paddle(Paddle(new Arduino('4', '3', serialValue), 40)),
          //   r_paddle(Paddle(new Arduino('2', '1', serialValue), width - 60)),
          score(Score()),
          paddlePos(playerPaddle)
    {
        if (playerPaddle == L)
        {
            rPaddle.setIsActive(false);
            lPaddle.setIsActive(true);
        }
        else
        {
            lPaddle.setIsActive(false);
            rPaddle.setIsActive(true);
        }
    };
    void loop();
    static const int height = 600;
    static const int width = 800;
    char *getSerialValuePtr();
    Paddle *getPaddle();
    Paddle *getOtherPaddle();
    void setBallView(int newX, int newY);

private:
    void handlePaddles();
    void checkAndPublishCollision();
    void checkIsOut();
    BallView ball;
    char *serialValue;
    Paddle lPaddle;
    Paddle rPaddle;
    Score score;
    PlayerPaddle paddlePos;
};

#endif
