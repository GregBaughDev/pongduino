#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

const std::string serverPort = "4950";

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    if (argc != 3) {
        std::cout << "usage: talker hostname message\n";
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], serverPort.c_str(), &hints, &servinfo)) != 0) {
        std::cout << "Error: getaddrinfo " << gai_strerror(rv);
    }

    // make a socket
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cout << "client: socket\n";
            continue;
        }

        break;
    };

    if (p == NULL) {
        std::cout << "client: failed to create socket\n";
        return 2;
    }

    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1) {
        std::cout << "client: sendto\n";
        exit(1);
    }

    freeaddrinfo(servinfo);

    std::cout << "client: sent " << numbytes << " bytes to " << argv[1] << "\n";
    close(sockfd);

    return 0;
}
