#include "pong.h"
#include "../controller/serialRead.h"
#include <thread>

int main()
{
    // SerialRead serialRead("/dev/ttyACM0");
    SerialRead serialRead("/dev/cu.usbmodem14101");

    Pong pong;
    pong.setup();

    std::thread input(&SerialRead::stream, serialRead, pong.getSerialPtr());

    pong.loop();

    input.join();

    return 0;
}
