#include "ball.h"

void Ball::handleBall()
{
    if (x >= 0 && y >= 0) {
        x -= speed;
        y -= speed;
    }
    DrawCircle(x, y, radius, colour);
}
