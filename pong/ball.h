#ifndef BALL_H
#define BALL_H
#include "raylib.h"

enum collisionPos { TOP, MID, BOTTOM };

class Ball
{
public:
    Ball(int x, int y) : radius(8.0), colour(RAYWHITE), x(x), y(y), speed(3){};
    void handleBall();
private:
    const float radius;
    const Color colour;
    int x;
    int y;
    int speed;
    void xTop();
    void xMid();
    void xBot();
};

#endif
