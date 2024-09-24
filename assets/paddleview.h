#ifndef PADDLEVIEW_H
#define PADDLEVIEW_H
#include "paddle.h"
#include "raylib.h"

class PaddleView
{
public:
    PaddleView()
        : rectangle{40, 100, Paddle::getWidth(), Paddle::getHeight()},
          colour{RED} {};
    void loop();
    void setRectangle(float newXPos, float newYPos);

private:
    Rectangle rectangle;
    Color colour;
};

#endif
