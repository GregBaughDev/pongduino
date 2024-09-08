#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <string>
#include <sstream>
#include <array>

/*
 * This struct holds the game data (sent from the server)
 */
typedef struct
{
    int ballPosX;
    int ballPosY;
    int lPaddlePosX;
    int lPaddlePosY;
    int rPaddlePosX;
    int rPaddlePosY;
} PongComm;

/*
 * This struct holds the client paddle data and which game instance is sending it (sent from client)
 */
typedef struct
{
    int paddleNum;
    int paddlePosX;
    int paddlePosY;
} PaddleComm;

class Communication
{
public:
    Communication()
        : stringStream(new std::stringstream) {};
    ~Communication()
    {
        delete stringStream;
    }

protected:
    void packageBytesInBuf(int value, int posB1, char *sendBuf);
    void unpackageBytesInBuf(int *value, int posB1, const char *rcvBuf);

private:
    std::stringstream *stringStream;
};

#endif
