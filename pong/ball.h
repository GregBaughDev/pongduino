#ifndef BALL_H
#define BALL_H
#include "raylib.h"

class Ball
{
public:
    Ball(float x, float y)
        : radius(8.0),
          colour(RAYWHITE),
          circle({x, y}),
          speedY(2),
          speedX(6),
          isStop(false){};
    void handleBall();
    Vector2 getCircle();
    float getRadius();
    void receiveHit(int colPos);
    void setIsStop();

private:
    void movementManager();
    void reverseX();
    void reverseY();
    const float radius;
    const Color colour;
    Vector2 circle;
    int speedY;
    int speedX;
    bool isStop;
};

#endif
