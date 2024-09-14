#include "paddleview.h"
#include <raylib.h>

void PaddleView::setRectangle(float newXPos, float newYPos)
{
    rectangle.x = newXPos;
    rectangle.y = newYPos;
}

void PaddleView::loop()
{
    DrawRectangleRec(rectangle, colour);
}
