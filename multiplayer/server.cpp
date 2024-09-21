#include "server.h"
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

/*
 * This function initialises the server and binds the server file descriptor to the port
 */
void Server::initialise()
{
    std::cout << "Initialising server...";
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM; // UDP
    hints.ai_flags = AI_PASSIVE;

    // get the internet address info that matches the request in hints
    // and store these in the servinfo structure (a linked list)
    int getAddrInfoRes;
    if ((getAddrInfoRes = getaddrinfo(NULL, serverPort.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "server: getaddrinfo failed -> " << gai_strerror(getAddrInfoRes) << "\n";
        exit(1);
    }

    // loop through the results and bind to the first
    struct addrinfo *p;
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((serverFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            continue;
        }

        if (bind(serverFd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(serverFd);
            std::cerr << "server: error binding port\n";
            exit(1);
        }

        break;
    }

    if (p == NULL)
    {
        std::cerr << "server: failed to bind the socket\n";
        exit(1);
    }

    freeaddrinfo(servinfo);
    std::cout << "server initialised\n";
}

/*
 * This function runs indefinitely. Upon receiving data from a client, it unpacks the received data,
 * updates the internal game state and sends the latest game state back to the client.
 */
void Server::run()
{
    std::cout << "Starting server on port " << serverPort << "\n";

    while (true)
    {
        addrLen = sizeof(clientAddr);
        if (recvfrom(serverFd, rcvBuf.get(), rcvBufLen, 0, (sockaddr *)&clientAddr, &addrLen) == -1)
        {
            std::cerr << "server: error receiving bytes " << strerror(errno) << "\n";
            close(serverFd);
            exit(2);
        }

        dataUnmarshall();
        updateGameStateFromPaddle();
        send();
    }
}

/*
 * This function unpacks the received client data into the paddleState struct
 */
void Server::dataUnmarshall()
{
    unpackageBytesInBuf(&rcvPaddle, 0, rcvBuf);

    if (rcvPaddle == 0)
    {
        unpackageBytesInBuf(&lPaddleState.paddlePosX, 2, rcvBuf);
        unpackageBytesInBuf(&lPaddleState.paddlePosY, 4, rcvBuf);
    }
    else
    {
        unpackageBytesInBuf(&rPaddleState.paddlePosX, 2, rcvBuf);
        unpackageBytesInBuf(&rPaddleState.paddlePosY, 4, rcvBuf);
    }
}

/*
 * This function packs the current paddleState into the send buffer
 */
void Server::dataMarshall()
{
    packageBytesInBuf(gameState.ballPosX, 0, sendBuf);
    packageBytesInBuf(gameState.ballPosY, 2, sendBuf);
    packageBytesInBuf(gameState.lPaddlePosX, 4, sendBuf);
    packageBytesInBuf(gameState.lPaddlePosY, 6, sendBuf);
    packageBytesInBuf(gameState.rPaddlePosX, 8, sendBuf);
    packageBytesInBuf(gameState.rPaddlePosY, 10, sendBuf);
}

/*
 * This function updates the game state depending on what paddle data has been received
 */
void Server::updateGameStateFromPaddle()
{
    if (rcvPaddle == 0)
    { // L paddle
        gameState.lPaddlePosX = lPaddleState.paddlePosX;
        gameState.lPaddlePosY = lPaddleState.paddlePosY;
    }
    else
    { // R paddle
        gameState.rPaddlePosX = rPaddleState.paddlePosX;
        gameState.rPaddlePosY = rPaddleState.paddlePosY;
    }
}

/*
 * This function marshalls the current paddleState into the send buffer (dataMarshall()) and sends it back to the last client who submitted data
 */
void Server::send()
{
    dataMarshall();
    if (sendto(serverFd, sendBuf.get(), sendBufLen, 0, (struct sockaddr *)&clientAddr, addrLen) < 0)
    {
        std::cerr << "Error sending to client -> " << strerror(errno) << "\n";
    }
}

/*
 * This function closes the server file descriptor
 */
void Server::closeResources()
{
    close(serverFd);
}
