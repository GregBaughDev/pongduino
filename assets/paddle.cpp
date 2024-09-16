#include "paddle.h"
#include "../pong/gamearea.h"
#include <raylib.h>

void Paddle::loop()
{
    handleMovement();
    DrawRectangleRec(rectangle, colour);
}

void Paddle::handleMovement()
{
    if (controller->isUpKeyDown() && rectangle.y > 0)
    {
        rectangle.y -= paddleSpeed;
    }
    else if (controller->isDownKeyDown() && (rectangle.y + height < GameArea::height))
    {
        rectangle.y += paddleSpeed;
    }
}

Rectangle Paddle::getRectangle()
{
    return rectangle;
}

void Paddle::setPaddle(int x, int y)
{
    rectangle.x = x;
    rectangle.y = y;
}

void Paddle::setIsActive(bool isActiveValue)
{
    isActive = isActiveValue;
}

float Paddle::getHeight()
{
    return height;
}

float Paddle::getWidth()
{
    return width;
}
