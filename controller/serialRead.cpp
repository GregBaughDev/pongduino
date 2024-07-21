#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

// https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
// http://www.unixwiz.net/techtips/termios-vmin-vtime.html

// current state - we're getting the information through but the loop needs to be sorted
// what should happen? Should we empty the buffer each time or use a ring buffer or something else?
int main()
{
    int serial_port = open("/dev/cu.usbmodem14101", O_RDONLY | O_NONBLOCK);
    struct termios tty;

    if (serial_port < 0)
    {
        std::cout << "Error opening serial port -> " << strerror(errno) << "\n";
        exit(1);
    }

    if (tcgetattr(serial_port, &tty) != 0)
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
    tty.c_cc[VMIN] = 255;

    // baud rate
    cfsetispeed(&tty, B9600); // set input baud rate to 9600

    // save the tty settings
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        std::cout << "Error from tcsetattr " << strerror(errno) << "\n";
        exit(1);
    }

    std::cout << "something has happened: " << serial_port << "\n";

    char readBuf[256];

    while (true)
    {
        read(serial_port, &readBuf, sizeof(readBuf));
        int i;
        for (i = 0; i < 256; i++)
        {
            if (readBuf[i] == '1' || readBuf[i] == '2' || readBuf[i] == '3' || readBuf[i] == '4')
            {
                std::cout << readBuf[i] << " ";
            }
        }
    }

    return 0;
}
