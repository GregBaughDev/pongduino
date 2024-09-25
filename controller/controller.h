#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <memory>

class Controller
{
public:
    virtual ~Controller() {};
    virtual bool isUpKeyDown() = 0;
    virtual bool isDownKeyDown() = 0;
    static std::unique_ptr<Controller> controllerFactory(char controllerType, char playerPos, char *serialValue);
};

#endif
