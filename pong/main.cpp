#include "pong.h"
#include "../controller/serialRead.h"
#include <thread>

// current state: so we now have a new thread for reading the serial data
// this is working while the game loop runs!
// Next steps are to write the code that communicates to the game loop.

int main()
{
    // SerialRead serialRead("/dev/ttyACM0");
    SerialRead serialRead("/dev/cu.usbmodem14201");

    Pong pong;
    pong.setup();

    std::thread input(&SerialRead::stream, serialRead, pong.getSerialPtr());

    pong.loop();

    input.join();

    return 0;
}
