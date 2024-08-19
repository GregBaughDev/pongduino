#include "pong.h"
#include "../controller/serialRead.h"
#include <thread>

int main()
{
    // SerialRead serialRead("/dev/ttyACM0");
    // SerialRead serialRead("/dev/cu.usbmodem142201");

    // instance one ("4950", "4951");
    // instance two ("4951", "4950");
    Pong pong("4950", "4951");
    // Pong pong("4951", "4950");
    pong.setup();

    // std::thread input(&SerialRead::stream, serialRead, pong.getSerialPtr());
    // input.detach();

    pong.loop();

    return 0;
}
