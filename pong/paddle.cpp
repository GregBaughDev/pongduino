#include "paddle.h"
#include "gameArea.h"
#include <raylib.h>

void Paddle::loop()
{
    handleMovement();
    DrawRectangleRec(rectangle, colour);
}

void Paddle::handleMovement()
{
    if (keyboard.isUpKeyDown() && rectangle.y >= 0)
    {
        rectangle.y -= paddleSpeed;
    }
    else if (keyboard.isDownKeyDown() && (rectangle.y + height <= GameArea::height))
    {
        rectangle.y += paddleSpeed;
    }
}

Rectangle Paddle::getRectangle()
{
    return rectangle;
}
