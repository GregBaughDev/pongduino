#include "paddlevirtual.h"

void PaddleVirtual::setRectangle(float newXPos, float newYPos)
{
    rectangle.x = newXPos;
    rectangle.y = newYPos;
}

Rectangle PaddleVirtual::getRectangle()
{
    return rectangle;
}
