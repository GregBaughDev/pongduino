#include <cstdlib>
#include <fcntl.h>
#include <iostream>

int main()
{
    int serial = open("/dev/ttyACM0", O_RDONLY | O_NONBLOCK);

    if (serial == -1) {
        std::cout << "serial is null\n";
        exit(1);
    }

    std::cout << "something has happened: " << serial << "\n";

    return 0;
}

