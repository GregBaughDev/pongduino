#ifndef BALL_H
#define BALL_H
#include "raylib.h"

enum Direction { LEFT, RIGHT, INITIAL };

class Ball
{
public:
    Ball(float x, float y) : radius(8.0), colour(RAYWHITE), circle({x, y}), speed(3), currDirr(INITIAL){};
    void handleBall();
    Vector2 getCircle();
    float getRadius();
    void receiveCollision(int colPos);
    const float radius;

private:
    const Color colour;
    Vector2 circle;
    int speed;
    Direction currDirr;
};

#endif
