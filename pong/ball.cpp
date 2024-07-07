#include "ball.h"
#include <iostream>
// to do - move public methods to top
void Ball::handleBall()
{
    if (currDirr == INITIAL)
    {
        circle.x -= speed;
    }

    DrawCircle(circle.x, circle.y, radius, colour);
}

Vector2 Ball::getCircle()
{
    return circle;
}

float Ball::getRadius()
{
    return radius;
}

void Ball::receiveCollision(int colPos)
{
    currDirr = RIGHT;
    if (colPos >= 0 && colPos < 20)
    {
        // how do we work out the direction?
        circle.x += speed;
    }

    if (colPos >= 20 && colPos < 40)
    {
        circle.x += speed;
    }

    if (colPos >= 40 && colPos < 60)
    {
        circle.x += speed;
    }

    if (colPos >= 60 && colPos < 80)
    {
        circle.x += speed;
    }

    if (colPos >= 80)
    {
        circle.x += speed;
    }
}
