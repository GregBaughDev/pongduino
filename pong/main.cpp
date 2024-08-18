#include "pong.h"
#include "../controller/serialRead.h"
#include <thread>

int main()
{
    // SerialRead serialRead("/dev/ttyACM0");
    SerialRead serialRead("/dev/cu.usbmodem142201");

    Pong pong;
    pong.setup();

    std::thread input(&SerialRead::stream, serialRead, pong.getSerialPtr());
    input.detach();

    pong.loop();

    return 0;
}
