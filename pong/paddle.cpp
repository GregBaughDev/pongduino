#include "paddle.h"
#include <raylib.h>
#include <iostream>

void Paddle::loop()
{
    handleMovement();
    DrawRectangleRec(m_rectangle, m_colour);
}

void Paddle::handleMovement()
{
    if (IsKeyDown(m_keyboard.getUpKey()) && m_rectangle.y >= 0)
    {
        m_rectangle.y -= 10;
    }
    else if (IsKeyDown(m_keyboard.getDownKey()) && (m_rectangle.y + height <= 600)) // don't hardcode this height
    {
        m_rectangle.y += 10;
    }
}

Rectangle Paddle::getRectangle()
{
    return m_rectangle;
}
