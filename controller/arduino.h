#ifndef ARDUINO_H
#define ARDUINO_H
#include "controller.h"

class Arduino : public Controller
{
public:
    Arduino(const char upKey, const char downKey, char *serialValuePtr)
        : upKey(upKey),
          downKey(downKey), serialValue(serialValuePtr) {};
    bool isDownKeyDown() override;
    bool isUpKeyDown() override;

private:
    const char upKey;
    const char downKey;
    char *serialValue;
};

#endif
