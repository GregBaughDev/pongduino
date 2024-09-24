#ifndef PADDLE_H
#define PADDLE_H
#include "../controller/controller.h"
#include "ball.h"
#include "raylib.h"

enum PlayerPaddle
{
    L,
    R
};
class Paddle
{
public:
    Paddle(Controller *inputType,
           float xPos)
        : paddleSpeed{25}, // 15 keyboard
          controller{inputType},
          rectangle{xPos, 250, width, height},
          colour{RAYWHITE} {};
    void loop();
    Rectangle getRectangle();
    void setPaddle(int x, int y);
    void setIsActive(bool isActive);
    static float getHeight();
    static float getWidth();
    static std::unique_ptr<Paddle> paddleFactory(Controller *controller, char playerPos);

private:
    void handleMovement();
    static constexpr float height = 100;
    static constexpr float width = 20;
    int paddleSpeed;
    Controller *controller;
    Rectangle rectangle;
    Color colour;
    bool isActive;
};

#endif
