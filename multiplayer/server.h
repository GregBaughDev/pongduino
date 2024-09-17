#ifndef SERVER_H
#define SERVER_H
#include "communication.h"
#include <string>
#include <arpa/inet.h>
#include <thread>

/*
 * Upon instantiation it will start the server on a new thread. This is joined
 * in the GameServer class.
 */
class Server : private Communication
{
public:
    Server(std::string port)
        : rcvBufLen(sizeof(PaddleComm)),
          rcvBuf(new char[rcvBufLen]),
          sendBufLen(sizeof(PongComm)),
          sendBuf(new char[sendBufLen]),
          gameState(PongComm({100, 200, 300, 400, 500, 600})),
          lPaddleState(PaddleComm({0, 0, 0})),
          rPaddleState(PaddleComm({0, 0, 0})),
          serverPort(port),
          rcvPaddle(0),
          Communication()
    {
        initialise();
        serverRunThread = std::thread(&Server::run, this);
    };
    ~Server()
    {
        delete[] rcvBuf;
        delete[] sendBuf;
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
    void dataUnmarshall();
    void dataMarshall();
    void updateGameStateFromPaddle();
    int rcvPaddle;
    int serverFd;
    std::string serverPort;
    int rcvBufLen;
    char *rcvBuf; // the server receives paddle data (PaddleComm)
    int sendBufLen;
    char *sendBuf; // the server sends the whole game state (PongComm)
    sockaddr_storage clientAddr;
    socklen_t addrLen;
};

#endif
