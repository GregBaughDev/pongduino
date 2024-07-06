#ifndef PADDLE_H
#define PADDLE_H
#include "keyboard.h"
#include "ball.h"
#include "raylib.h"

class Paddle
{
public:
    Paddle(Keyboard keyboard, float xPos, Ball ball)
        : width(20), 
        height(100), 
        yPos(20), 
        xPos(xPos), 
        m_keyboard(keyboard), 
        m_ball(ball),
        m_rectangle({xPos, yPos, width, height}),
        m_colour(RAYWHITE){};
    void loop();

private:
    void handleMovement();
    void handleCollision();
    void publishCollision();
    const float width;
    const float height;
    const float yPos;
    const float xPos;
    // let's just do this as keyboard for now
    // and come back to setting it as a interface
    Keyboard m_keyboard;
    Ball m_ball;
    Rectangle m_rectangle;
    Color m_colour;
    // make all private members m_
};

#endif
