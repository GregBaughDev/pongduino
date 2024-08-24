#include "paddle.h"
#include "../pong/gameArea.h"
#include <raylib.h>

void Paddle::loop()
{
    if (isActive)
    {
        handleMovement();
    }
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
