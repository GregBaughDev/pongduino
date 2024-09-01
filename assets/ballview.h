#ifndef BALLVIEW_H
#define BALLVIEW_H
#include "raylib.h"

class BallView
{
public:
    BallView()
        : colour(RAYWHITE) {};
    void loop();
    void setCircle(int newX, int newY);

private:
    Vector2 circle;
    Color colour;
};

#endif
