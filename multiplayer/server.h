#ifndef SERVER_H
#define SERVER_H
#include "communication.h"
#include <string>
#include <arpa/inet.h>
#include <thread>

/*
 * Upon instantiation it will start the server on a new thread and handle
 * communication with the game clients
 */
class Server : private Communication
{
public:
    Server(std::string port,
           int clientPort1,
           int clientPort2)
        : rcvBufLen(sizeof(PaddleComm)),
          rcvBuf(new char[rcvBufLen]),
          sendBufLen(sizeof(PongComm)),
          sendBuf(new char[sendBufLen]),
          gameState(new PongComm({100, 200, 300, 400, 500, 600})),
          paddleState(new PaddleComm({0, 0, 0})),
          serverPort(port),
          Communication()
    {
        initialise();
        std::thread serverRunThread(&Server::run, this);

        serverRunThread.join();
    };

private:
    void run();
    void initialise();
    void closeResources();
    void send();
    void dataUnmarshall();
    void dataMarshall();
    void updateGameStateFromPaddle();
    int serverFd;
    std::string serverPort;
    int rcvBufLen;
    char *rcvBuf; // the server receives paddle data (PaddleComm)
    int sendBufLen;
    char *sendBuf; // the server sends the whole game state (PongComm)
    PongComm *gameState;
    PaddleComm *paddleState;
    sockaddr_storage clientAddr;
    socklen_t addrLen;
};

#endif
