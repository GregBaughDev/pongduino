#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "controller.h"

class Keyboard : public Controller
{
public:
    Keyboard(const int upKey, const int downKey)
        : upKey{upKey},
          downKey{downKey} {};
    bool isDownKeyDown() override;
    bool isUpKeyDown() override;

private:
    const int upKey;
    const int downKey;
};

#endif
