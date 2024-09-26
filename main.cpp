#include "./pong/pong.h"
#include "./controller/serialRead.h"
#include <thread>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Pong - Provide: \n"
                  << "**controller** Keyboard (k) or Arduino (a)\n"
                  << "**player** 1 or 2\n";
        exit(1);
    }

    char controller = argv[1][0];

    if (controller != 'k' && controller != 'a')
    {
        std::cerr << "usage: k || a\n";
        exit(1);
    }

    char player = argv[2][0];

    if (player != '1' && player != '2')
    {
        std::cerr << "usage: 1 || 2\n";
        exit(1);
    }

    std::unique_ptr<char> serialValue = std::make_unique<char>('0');
    std::unique_ptr<Controller> controllerPtr = Controller::controllerFactory(controller, player, serialValue.get());
    std::unique_ptr<Paddle> paddlePtr = Paddle::paddleFactory(controllerPtr.get(), player);
    std::unique_ptr<Pong> pongPtr = std::make_unique<Pong>("4951", player == '1' ? L : R, *paddlePtr);

    if (controller == 'a')
    {
        std::string arduinoPort = argv[3];
        SerialRead serialRead(arduinoPort);
        std::thread input(&SerialRead::stream, serialRead, serialValue.get());

        input.detach();
    }

    pongPtr.get()->loop();

    return 0;
}
