#include "controller.h"
#include "keyboard.h"
#include "arduino.h"
#include <raylib.h>

std::unique_ptr<Controller> Controller::controllerFactory(char controllerType, char playerPos, char *serialValue)
{
    std::unique_ptr<Controller> controller;

    if (controllerType == 'k')
    {
        controller = std::make_unique<Keyboard>(
            playerPos == '1' ? KEY_E : KEY_UP,
            playerPos == '1' ? KEY_X : KEY_DOWN);
    }
    else if (controllerType == 'a')
    {
        controller = std::make_unique<Arduino>(
            playerPos == '1' ? '4' : '2',
            playerPos == '1' ? '3' : '1',
            serialValue);
    }

    return controller;
}
