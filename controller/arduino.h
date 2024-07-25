#ifndef ARDUINO_H
#define ARDUINO_H
#include "controller.h"

class Arduino : public Controller
{
public:
    Arduino(const int upKey, const int downKey)
        : upKey(upKey),
          downKey(downKey){};
    int getDownKey() override
    {
        return downKey;
    }
    int getUpKey() override
    {
        return upKey;
    }

private:
    const int upKey;
    const int downKey;
};

#endif
