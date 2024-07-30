#include "serialRead.h"
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <ostream>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <thread>

// based on these articles
// https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
// http://www.unixwiz.net/techtips/termios-vmin-vtime.html

// to read
// https://tldp.org/HOWTO/Serial-Programming-HOWTO/

void SerialRead::setup()
{
    portFd = open(serialPort.c_str(), O_RDONLY | O_NONBLOCK);

    struct termios tty;

    if (portFd < 0)
    {
        std::cout << "Error opening serial port -> " << strerror(errno) << "\n";
        exit(1);
    }

    if (tcgetattr(portFd, &tty) != 0)
    {
        std::cout << "Error from tcgetattr -> " << strerror(errno) << "\n";
        exit(1);
    }

    // control modes (cflags)
    tty.c_cflag &= ~PARENB; // Disable parity bit
    tty.c_cflag &= ~CSTOPB; // Only use one stop bit in communication
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;       // Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver and ignore modem status lines

    // local modes (lflags)
    tty.c_lflag &= ~ICANON; // Non-canonical mode (allows us to process raw serial data)
    tty.c_lflag &= ~ECHO;   // disable echo
    tty.c_lflag &= ~ECHOE;  // disable erasure
    tty.c_lflag &= ~ECHONL; // disable new line echo
    tty.c_lflag &= ~ISIG;   // disable interpreting INTR, QUIT & SUSP

    // input modes (iflags)
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // disable software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // disables special handling of received bytes, allows us to access raw bytes

    // output modes (oflags)
    tty.c_oflag &= ~OPOST; // disable special interpretation of output bytes (i.e. newline)
    tty.c_oflag &= ~ONLCR; // disable conversion of newline to carriage return

    // VMIN, VTIME
    // may need to experiment with these if they block the thread
    tty.c_cc[VTIME] = 1; // wait up to a second, returning as soon as any data is received
    tty.c_cc[VMIN] = 1;  // this was changed from 255 in case it breaks

    // baud rate
    cfsetispeed(&tty, B9600); // set input baud rate to 9600

    // save the tty settings
    if (tcsetattr(portFd, TCSANOW, &tty) != 0)
    {
        std::cout << "Error from tcsetattr " << strerror(errno) << "\n";
        exit(1);
    }
}

void SerialRead::stream(char *valueStore)
{
    char readBuf[1];

    while (true)
    {
        read(portFd, &readBuf, sizeof(readBuf));
        *valueStore = readBuf[0];
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}
