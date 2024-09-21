#ifndef CLIENT_H
#define CLIENT_H
#include "communication.h"
#include <string>

class Client : private Communication
{
public:
    Client(std::string port, PongComm *gameData, PaddleComm *paddleData)
        : serverPort{port},
          rcvBufLen{sizeof(PongComm)},
          rcvBuf{new char[rcvBufLen]},
          sendBufLen{sizeof(PaddleComm)},
          sendBuf{new char[sendBufLen]},
          gameState{gameData},
          paddleState{paddleData},
          Communication{}
    {
        initialise();
    };
    ~Client()
    {
        closeResources();
        delete[] rcvBuf;
        delete[] sendBuf;
    };
    void send();

private:
    void initialise();
    void receive();
    void dataUnmarshall(); // TODO add this and below to interfaces
    void dataMarshall();
    void closeResources();
    std::string serverPort;
    struct addrinfo *serverAddress;
    int serverFd;
    int rcvBufLen; // this will be the whole struct
    char *rcvBuf;
    int sendBufLen;
    char *sendBuf; // this will be the paddle data
    PongComm *gameState;
    PaddleComm *paddleState;
};

#endif
