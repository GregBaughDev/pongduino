#include "keyboard.h"
#include <raylib.h>

bool Keyboard::isDownKeyDown()
{
    return IsKeyDown(downKey);
}

bool Keyboard::isUpKeyDown()
{
    return IsKeyDown(upKey);
}
