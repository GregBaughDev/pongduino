#ifndef CLIENT_H
#define CLIENT_H
#include "communication.h"
#include <string>

class Client : private Communication
{
public:
    Client(std::string port)
        : serverPort(port),
          rcvBufLen(sizeof(PongComm)),
          rcvBuf(new char[rcvBufLen]),
          sendBufLen(sizeof(PaddleComm)),
          sendBuf(new char[sendBufLen]),
          gameState(new PongComm({0, 0, 0, 0, 0, 0})),
          paddleState(new PaddleComm({1, 220, 330})),
          Communication()
    {
        initialise();
    };
    ~Client()
    {
        delete[] rcvBuf;
        delete[] sendBuf;
        delete gameState;
        delete paddleState;

        closeResources();
    };
    void send(); // TODO move this somewhere else, can it be protected?
    PongComm *gameState;

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
    PaddleComm *paddleState;
};

#endif

// Current state
// we have the communication between the client and server happening.
// next we need to update the game server and two instances of the game

// replace new and delete with stack pointers
// or do it all with shared pointers - come back to this
