#ifndef SERIAL_READ_H
#define SERIAL_READ_H
#include <string>

// linux -> "/dev/ttyACM0"
// mac -> "/dev/cu.usbmodem14101"

class SerialRead
{
public:
    SerialRead(std::string port)
        : serialPort{port}
    {
        setup();
    };
    void stream(char *valueStore);

private:
    void setup();
    std::string serialPort;
    int portFd;
};

#endif
