#include "arduino.h"

bool Arduino::isDownKeyDown()
{
    return downKey == *serialValue;
}

bool Arduino::isUpKeyDown()
{
    return upKey == *serialValue;
}
