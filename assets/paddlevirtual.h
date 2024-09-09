#ifndef PADDLEVIEW_H
#define PADDLEVIEW_H
#include "paddle.h"
#include "raylib.h"

/*
 * Class used in the gameserver to handle the game logic. Cut down version of
 * Paddle but without any data to handle displaying the paddle.
 */
class PaddleVirtual
{
public:
    PaddleVirtual()
        : rectangle({0, 250, Paddle::getWidth(), Paddle::getHeight()}) {};
    void setRectangle(float newXPos);

private:
    Rectangle rectangle;
};

#endif
