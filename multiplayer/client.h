#ifndef CLIENT_H
#define CLIENT_H
#include "communication.h"
#include <string>
#include <memory>

class Client : private Communication
{
public:
    Client(
        std::string port,
        std::shared_ptr<PongComm> gameData,
        std::shared_ptr<PaddleComm> paddleData)
        : serverPort{port},
          rcvBufLen{sizeof(PongComm)},
          rcvBuf{std::make_shared<char[]>(char(rcvBufLen))},
          sendBufLen{sizeof(PaddleComm)},
          sendBuf{std::make_shared<char[]>(char(sendBufLen))},
          gameState{gameData},
          paddleState{paddleData},
          Communication{}
    {
        initialise();
    };
    ~Client()
    {
        closeResources();
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
    std::shared_ptr<char[]> rcvBuf;
    int sendBufLen;
    std::shared_ptr<char[]> sendBuf;
    std::shared_ptr<PongComm> gameState;
    std::shared_ptr<PaddleComm> paddleState;
};

#endif
