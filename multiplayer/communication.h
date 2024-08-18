#ifndef COMMUNICATION_H
#define COMMUNICATION_H
// #include "../pong/pong.h"
#include <string>
#include <sstream>
#include <array>

// chuck this here for testing (remove!)
struct
{
    int ballPosX;
    int ballPosY;
    int paddlePosX;
    int paddlePosY;
} typedef PongCommTest;

class Communication
{
public:
    Communication(
        std::string myPort,
        std::string theirPort)
        : rcvPort(myPort),
          sndPort(theirPort),
          stringStream(new std::stringstream),
          rcvComm(new PongCommTest({0, 0, 0, 0})),
          sndComm(new PongCommTest({100, 69, 800, 123})),
          sendBuf(new char[maxBufLen]),
          rcvBuf(new char[maxBufLen])
    {
        initialiseServer();
        initialiseClient();
    };
    ~Communication()
    {
        closeResources();
        // we also need to delete everything here created with new
    };
    void startServer();
    void clientSend();
    const static int maxBufLen = 8;

private:
    void initialiseServer();
    void initialiseClient();
    void closeResources();
    void dataMarshall();
    void dataUnmarshall();
    void packageBytesInBuf(int value, int posB1);
    void unpackageBytesInBuf(int *value, int posB1);
    std::string rcvPort;
    std::string sndPort;
    int rcvFd;
    int sndFd;
    char *rcvBuf;
    char *sendBuf;
    struct addrinfo *serverAddress;
    std::stringstream *stringStream;
    PongCommTest *rcvComm;
    PongCommTest *sndComm;
};

#endif
