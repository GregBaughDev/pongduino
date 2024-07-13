#include "ball.h"
#include "gameArea.h"
#include <iostream>

void Ball::handleBall()
{
    if (!isStop)
    {
        movementManager();
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

void Ball::receiveHit(int colPos)
{
    reverseX();
    reverseY();

    if (colPos >= 0 && colPos < 10)
    {
        speedY += 6;
    }

    if (colPos >= 10 && colPos < 20)
    {
        speedY += 5;
    }

    if (colPos >= 30 && colPos < 40)
    {
        speedY += 4;
    }

    if (colPos >= 40 && colPos < 50)
    {
        speedY += 3;
    }

    if (colPos >= 50 && colPos < 60)
    {
        speedY -= 1;
    }

    if (colPos >= 60 && colPos < 70)
    {
        speedY += 3;
    }

    if (colPos >= 70 && colPos < 80)
    {
        speedY -= 4;
    }

    if (colPos >= 80 && colPos < 90)
    {
        speedY -= 5;
    }

    if (colPos >= 90)
    {
        speedY -= 6;
    }
}

void Ball::setIsStop()
{
    isStop = true;
}

void Ball::movementManager()
{
    if (circle.y <= 0)
    {
        reverseY();
    }

    if (circle.y >= GameArea::height)
    {
        reverseY();
    }

    if (circle.x <= 0)
    {
        reverseX();
    }

    if (circle.x >= GameArea::width)
    {
        reverseX();
    }

    circle.x -= speedX;
    circle.y -= speedY;
}

void Ball::reverseX()
{
    speedX = -speedX;
}

void Ball::reverseY()
{
    speedY = -speedY;
}
