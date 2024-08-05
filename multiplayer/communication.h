#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <string>

class Communication
{
public:
    Communication(
        std::string myPort,
        std::string theirPort) : rcvPort(myPort), sndPort(theirPort)
    {
        initialiseServer();
        initialiseClient();
    }
    ~Communication()
    {
        closeResources();
    }
    void startServer();
    void clientSend();
    const static int maxBufLen = 10;

private:
    void initialiseServer();
    void initialiseClient();
    void closeResources();
    std::string rcvPort;
    std::string sndPort;
    int rcvFd;
    int sndFd;
    char buf[maxBufLen];
    struct addrinfo *serverAddress;
};

#endif
