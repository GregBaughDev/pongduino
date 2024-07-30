#ifndef PADDLE_H
#define PADDLE_H
#include "../controller/controller.h"
#include "ball.h"
#include "raylib.h"

class Paddle
{
public:
    Paddle(Controller *inputType, float xPos)
        : width(20),
          height(100),
          paddleSpeed(30), // 15 keyboard
          controller(inputType),
          rectangle({xPos, 20, width, height}),
          colour(RAYWHITE) {};
    void loop();
    Rectangle getRectangle();

private:
    void handleMovement();
    const float width;
    const float height;
    int paddleSpeed;
    Controller *controller;
    Rectangle rectangle;
    Color colour;
};

#endif
