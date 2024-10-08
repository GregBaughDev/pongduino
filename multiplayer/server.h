#ifndef SERVER_H
#define SERVER_H
#include "communication.h"
#include <string>
#include <arpa/inet.h>
#include <thread>
#include <memory>

/*
 * Upon instantiation it will start the server on a new thread. This is joined
 * in the GameServer class.
 */
class Server : private Communication
{
public:
    Server(std::string port)
        : Communication{},
          gameState{PongComm{0, 0, 0, 0, 0, 0}},
          lPaddleState{PaddleComm{0, 0, 0}},
          rPaddleState{PaddleComm{0, 0, 0}},
          rcvPaddle{0},
          serverPort{port},
          rcvBufLen{sizeof(PaddleComm)},
          rcvBuf{std::make_unique<char[]>(char(rcvBufLen))},
          sendBufLen{sizeof(PongComm)},
          sendBuf{std::make_unique<char[]>(char(sendBufLen))}
    {
        initialise();
        serverRunThread = std::thread{&Server::run, this};
    };
    ~Server()
    {
        closeResources();
    };

protected:
    PongComm gameState;
    PaddleComm lPaddleState;
    PaddleComm rPaddleState;
    std::thread serverRunThread;

private:
    void send();
    void run();
    void initialise();
    void closeResources();
    void dataUnmarshall() override;
    void dataMarshall() override;
    void updateGameStateFromPaddle();
    int rcvPaddle;
    int serverFd;
    std::string serverPort;
    int rcvBufLen;
    std::unique_ptr<char[]> rcvBuf; // the server receives paddle data (PaddleComm)
    int sendBufLen;
    std::unique_ptr<char[]> sendBuf; // the server sends the whole game state (PongComm)
    sockaddr_storage clientAddr;
    socklen_t addrLen;
};

#endif
