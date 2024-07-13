#include "paddle.h"
#include "gameArea.h"
#include <raylib.h>
#include <iostream>

void Paddle::loop()
{
    handleMovement();
    DrawRectangleRec(rectangle, colour);
}

void Paddle::handleMovement()
{
    if (IsKeyDown(keyboard.getUpKey()) && rectangle.y >= 0)
    {
        rectangle.y -= paddleSpeed;
    }
    else if (IsKeyDown(keyboard.getDownKey()) && (rectangle.y + height <= GameArea::height))
    {
        rectangle.y += paddleSpeed;
    }
}

Rectangle Paddle::getRectangle()
{
    return rectangle;
}
