#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    virtual bool isUpKeyDown() = 0;
    virtual bool isDownKeyDown() = 0;
};

#endif
