#include "client.h"
#include <iostream>
#include <netdb.h>
#include <unistd.h>

/*
 * Initialise the client and set the serverAddress to the server
 */
void Client::initialise()
{
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;

    int getAddrInfoRes;
    if ((getAddrInfoRes = getaddrinfo("localhost", serverPort.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "client: getaddrinfo failed -> " << gai_strerror(getAddrInfoRes) << "\n";
        exit(1);
    }

    for (serverAddress = servinfo; serverAddress != NULL; serverAddress = serverAddress->ai_next)
    {
        if ((serverFd = socket(serverAddress->ai_family, serverAddress->ai_socktype, serverAddress->ai_protocol)) == -1)
        {
            continue;
        }

        break;
    }

    if (serverAddress == NULL)
    {
        std::cerr << "client: failed to set the server address\n";
        exit(1);
    }
}

/*
 * Prepare the current paddle data to be sent (dataMarshall()), send the data to the server and
 * wait for the server to respond with the current game state
 */
void Client::send()
{
    dataMarshall();

    int bytesSent;
    if ((bytesSent = sendto(serverFd, sendBuf.get(), sendBufLen, 0, serverAddress->ai_addr, serverAddress->ai_addrlen)) == -1)
    {
        std::cerr << "client: failed to send. errno -> " << strerror(errno) << "\n";
        exit(2);
    }

    receive();
}

/*
 * Receive the current game state from the server and update the client game state (dataUnmarshall())
 */
void Client::receive()
{
    if (recvfrom(serverFd, rcvBuf.get(), rcvBufLen, 0, nullptr, nullptr) == -1)
    {
        std::cerr << "client: error receiving bytes " << strerror(errno) << "\n";
        close(serverFd);
        exit(2);
    }

    dataUnmarshall();
}

/*
 * Copy the data received from the server back into the clients copy of the state
 */
void Client::dataUnmarshall()
{
    unpackageBytesInBuf(&gameState->ballPosX, 0, rcvBuf.get());
    unpackageBytesInBuf(&gameState->ballPosY, 2, rcvBuf.get());
    unpackageBytesInBuf(&gameState->lPaddlePosX, 4, rcvBuf.get());
    unpackageBytesInBuf(&gameState->lPaddlePosY, 6, rcvBuf.get());
    unpackageBytesInBuf(&gameState->rPaddlePosX, 8, rcvBuf.get());
    unpackageBytesInBuf(&gameState->rPaddlePosY, 10, rcvBuf.get());
}

/*
 * Prepare the client data to be sent to the server
 */
void Client::dataMarshall()
{
    packageBytesInBuf(paddleState->paddleNum, 0, sendBuf.get());
    packageBytesInBuf(paddleState->paddlePosX, 2, sendBuf.get());
    packageBytesInBuf(paddleState->paddlePosY, 4, sendBuf.get());
}

/*
 * This function closes the server file descriptor
 */
void Client::closeResources()
{
    close(serverFd);
}
