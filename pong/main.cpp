#include "pong.h"
#include "../controller/serialRead.h"
#include "../multiplayer/gameserver.h"
#include <thread>

int main()
{
    // SerialRead serialRead("/dev/ttyACM0");
    // SerialRead serialRead("/dev/cu.usbmodem142201");
    // std::thread input(&SerialRead::stream, serialRead, pong.getSerialPtr());
    // input.detach();

    // Pong pong("4951", L);
    Pong pong("4951", R);
    pong.loop();

    // GameServer gameserver("4951");

    return 0;
}
