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
          paddleSpeed(25), // 15 keyboard
          controller(inputType),
          rectangle({xPos, 20, width, height}),
          colour(RAYWHITE) {};
    void loop();
    Rectangle getRectangle();
    void setPaddle(int x, int y);
    void setIsActive(bool isActive);
private:
    void handleMovement();
    const float width;
    const float height;
    int paddleSpeed;
    Controller *controller;
    Rectangle rectangle;
    Color colour;
    bool isActive;
};

#endif
