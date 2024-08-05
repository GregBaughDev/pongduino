#include "communication.h"
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

void Communication::initialiseServer()
{
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM; // UDP
    hints.ai_flags = AI_PASSIVE;

    // get the internet address info that matches the request in hints
    // and store these in the servinfo structure (a linked list)
    int getAddrInfoRes;
    if ((getAddrInfoRes = getaddrinfo(NULL, rcvPort.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "server: getaddrinfo failed -> " << gai_strerror(getAddrInfoRes) << "\n";
        exit(1);
    }

    // loop through the results and bind to the first
    struct addrinfo *p;
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((rcvFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            continue;
        }

        if (bind(rcvFd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(rcvFd);
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
}

void Communication::startServer()
{
    struct sockaddr_storage theirAddr;
    socklen_t addrLen = sizeof theirAddr;
    int receivedBytes;

    std::cout << "Server starting on " << rcvPort << "\n";

    while (true)
    {
        if ((receivedBytes = recvfrom(rcvFd, buf, maxBufLen, 0, (struct sockaddr *)&theirAddr, &addrLen)) == -1)
        {
            std::cerr << "error receiving bytes\n";
            exit(2);
        }
        std::cout << "received -> " << buf << "\n";
    }
}

void Communication::closeResources()
{
    close(rcvFd);
    close(sndFd);
}

void Communication::initialiseClient()
{
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;

    int getAddrInfoRes;
    if ((getAddrInfoRes = getaddrinfo("localhost", sndPort.c_str(), &hints, &servinfo)) != 0)
    {
        std::cerr << "client: getaddrinfo failed -> " << gai_strerror(getAddrInfoRes) << "\n";
        exit(1);
    }

    for (serverAddress = servinfo; serverAddress != NULL; serverAddress = serverAddress->ai_next)
    {
        if ((sndFd = socket(serverAddress->ai_family, serverAddress->ai_socktype, serverAddress->ai_protocol)) == -1)
        {
            continue;
        }

        break;
    }

    if (serverAddress == NULL)
    {
        std::cerr << "client: failed to bind the socket\n";
        exit(1);
    }
}

void Communication::clientSend() // eventually this will take a struct or similar to send - for now let's hardcode it
{
    int bytesSent;
    if ((bytesSent = sendto(sndFd, "112369813\0", maxBufLen, 0, serverAddress->ai_addr, serverAddress->ai_addrlen)) == -1)
    {
        std::cerr << "client: failed to send. errno -> " << strerror(errno) << "\n";
        exit(2);
    }
}
