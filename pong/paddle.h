#ifndef PADDLE_H
#define PADDLE_H
#include "../controller/keyboard.h"
#include "ball.h"
#include "raylib.h"

class Paddle
{
public:
    Paddle(Keyboard keyboard, float xPos)
        : width(20),
          height(100),
          paddleSpeed(15),
          keyboard(keyboard),
          rectangle({xPos, 20, width, height}),
          colour(RAYWHITE){};
    void loop();
    Rectangle getRectangle();

private:
    void handleMovement();
    const float width;
    const float height;
    int paddleSpeed;
    // let's just do this as keyboard for now
    // and come back to setting it as a interface
    Keyboard keyboard;
    Rectangle rectangle;
    Color colour;
};

#endif
