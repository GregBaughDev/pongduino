#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

const std::string myport = "4950";
constexpr int maxBufLen = 100;

// based on Beej's network programming guide

// get sockAddr
void *getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main()
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage theirAddr;
    char buf[maxBufLen];
    socklen_t addrLen;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM; // UDP
    hints.ai_flags = AI_PASSIVE;

    // get the internet address info that matches the request in hints
    // and store these in the servinfo structure as a linked list
    if ((rv = getaddrinfo(NULL, myport.c_str(), &hints, &servinfo)) != 0) {
        std::cout << " getaddrinfo: " << gai_strerror(rv);
        return 1;
    }

    // loop through the results and bind to the first
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cout << "listener: socket\n";
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            std::cout << "listener: bind\n";
            continue;
        }

        break;
    }

    if (p == NULL) {
        std::cout << "listener: failed to bind socket\n";
        return 2;
    }

    freeaddrinfo(servinfo);

    std::cout << "listener: waiting to receive....\n";

    addrLen = sizeof theirAddr;

    if ((numbytes = recvfrom(sockfd, buf, maxBufLen - 1, 0, (struct sockaddr *)&theirAddr, &addrLen)) == -1) {
        std::cout << "listener: error -> recvfrom\n";
        exit(1);
    };

    std::cout << "listener: got packet from " << inet_ntop(theirAddr.ss_family, getInAddr((struct sockaddr *)&theirAddr), s, sizeof s) << "\n";
    std::cout << "listener: packet is " << numbytes << " bytes long\n";
    buf[numbytes] = '\0';
    std::cout << "listener: packet contains " << buf << "\n";

    close(sockfd);

    return 0;
}

