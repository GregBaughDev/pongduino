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
        PongComm *gameData,
        PaddleComm *paddleData)
        : Communication{},
          serverPort{port},
          rcvBufLen{sizeof(PongComm)},
          rcvBuf{std::make_unique<char[]>(char(rcvBufLen))},
          sendBufLen{sizeof(PaddleComm)},
          sendBuf{std::make_unique<char[]>(char(sendBufLen))},
          gameState{gameData},
          paddleState{paddleData}
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
    void dataUnmarshall() override;
    void dataMarshall() override;
    void closeResources();
    std::string serverPort;
    struct addrinfo *serverAddress;
    int serverFd;
    int rcvBufLen;
    std::unique_ptr<char[]> rcvBuf;
    int sendBufLen;
    std::unique_ptr<char[]> sendBuf;
    PongComm *gameState;
    PaddleComm *paddleState;
};

#endif
