#include "pong.h"
#include <iostream>
#include "raylib.h"

int main()
{
    Pong pong;
    pong.setup();
    pong.loop();

    return 0;
}
