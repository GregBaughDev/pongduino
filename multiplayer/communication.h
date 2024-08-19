#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <string>
#include <sstream>
#include <array>

typedef struct
{
    int ballPosX;
    int ballPosY;
    int paddlePosX;
    int paddlePosY;
} PongComm;

class Communication
{
public:
    Communication(
        std::string thisPort,
        std::string theirPort,
        PongComm *thisData,
        PongComm *thatData)
        : rcvPort(thisPort),
          sndPort(theirPort),
          stringStream(new std::stringstream),
          rcvComm(thatData),
          sndComm(thisData),
          sendBuf(new char[maxBufLen]),
          rcvBuf(new char[maxBufLen])
    {
        initialiseServer();
        initialiseClient();
    };
    ~Communication()
    {
        closeResources();
        delete stringStream;
        delete[] sendBuf;
        delete[] rcvBuf;
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
    PongComm *rcvComm;
    PongComm *sndComm;
};

#endif
