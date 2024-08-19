#include "communication.h"
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <bitset>
#include <sstream>

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

    while (true)
    {
        if (recvfrom(rcvFd, rcvBuf, maxBufLen, 0, (struct sockaddr *)&theirAddr, &addrLen) == -1)
        {
            std::cerr << "error receiving bytes " << strerror(errno) << "\n";
            exit(2);
        }

        dataUnmarshall();
        // to do - remove once tested
        std::cout << "ballPosX is " << rcvComm->ballPosX << "\n";
        std::cout << "ballPosY is " << rcvComm->ballPosY << "\n";
        std::cout << "paddlePosX is " << rcvComm->paddlePosX << "\n";
        std::cout << "paddlePosY is " << rcvComm->paddlePosY << "\n";
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

void Communication::clientSend()
{
    dataMarshall();

    int bytesSent;
    if ((bytesSent = sendto(sndFd, sendBuf, maxBufLen, 0, serverAddress->ai_addr, serverAddress->ai_addrlen)) == -1)
    {
        std::cerr << "client: failed to send. errno -> " << strerror(errno) << "\n";
        exit(2);
    }
}

void Communication::dataUnmarshall()
{
    unpackageBytesInBuf(&rcvComm->ballPosX, 0);
    unpackageBytesInBuf(&rcvComm->ballPosY, 2);
    unpackageBytesInBuf(&rcvComm->paddlePosX, 4);
    unpackageBytesInBuf(&rcvComm->paddlePosY, 6);
}

void Communication::dataMarshall()
{
    packageBytesInBuf(sndComm->ballPosX, 0);
    packageBytesInBuf(sndComm->ballPosY, 2);
    packageBytesInBuf(sndComm->paddlePosX, 4);
    packageBytesInBuf(sndComm->paddlePosY, 6);
}

void Communication::unpackageBytesInBuf(int *value, int posB1)
{
    // to do - can we reuse bitset classes save instantiating each time?
    std::bitset firstPos = std::bitset<8>(rcvBuf[posB1]);
    std::bitset secondPos = std::bitset<8>(rcvBuf[posB1 + 1]);
    std::bitset result = std::bitset<16>(firstPos.to_ulong() << firstPos.size() | secondPos.to_ulong());

    *value = static_cast<int>(result.to_ulong());
}

void Communication::packageBytesInBuf(int value, int posB1)
{
    std::bitset ballPosXBs = std::bitset<16>(value);

    char b1 = 0;
    char b2 = 0;
    int i;

    for (i = 15; i >= 0; i--)
    {
        if (i > 7)
        {
            b1 <<= 1;
            b1 |= ballPosXBs[i];
        }
        else
        {
            b2 <<= 1;
            b2 |= ballPosXBs[i];
        }
    }

    // convert it to byte
    *stringStream << std::hex << b1;

    std::string b1HexString = stringStream->str();
    unsigned char b1Char = static_cast<unsigned char>(std::strtol(b1HexString.c_str(), nullptr, 16));

    stringStream->str("");

    *stringStream << std::hex << b2;
    std::string b2HexString = stringStream->str();
    unsigned char b2Char = static_cast<unsigned char>(std::strtol(b2HexString.c_str(), nullptr, 16));

    stringStream->str("");

    sendBuf[posB1] = b1;
    sendBuf[posB1 + 1] = b2;
}
