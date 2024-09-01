#ifndef BALL_H
#define BALL_H
#include "raylib.h"

class Ball
{
public:
    Ball(float x, float y)
        : colour(RAYWHITE),
          circle({x, y}),
          speedY(2),
          speedX(6),
          isStop(false) {};
    void handleBall();
    Vector2 getCircle();
    static float getRadius();
    void receiveHit(int colPos);
    void setIsStop();

private:
    void movementManager();
    void reverseX();
    void reverseY();
    static constexpr float radius = 8.0;
    const Color colour;
    Vector2 circle;
    int speedY;
    int speedX;
    bool isStop;
};

#endif
