#include "ballview.h"
#include "ball.h"

void BallView::loop()
{
    DrawCircle(circle.x, circle.y, Ball::getRadius(), colour);
}

void BallView::setCircle(int newX, int newY)
{
    circle.x = newX;
    circle.y = newY;
}
