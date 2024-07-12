#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "controller.h"

class Keyboard : public Controller
{
public:
    Keyboard(const int upKey, const int downKey) : upKey(upKey), downKey(downKey) {};
    int getDownKey() override {
        return downKey;
    }
    int getUpKey() override {
        return upKey;
    }
private:
    const int upKey;
    const int downKey;
};

#endif