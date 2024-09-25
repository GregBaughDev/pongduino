#include "communication.h"
#include <bitset>
#include <memory>

/*
 * Unpacks two bytes from a provided char buffer and sets the value of the
 * provided int pointer to the result
 *
 * @param *value pointer to the value which the result will be set to
 * @param posB1 the position of the required value to be unpacked in the buffer
 * @param rcvBuf pointer to the character buffer the values should be unpackaged from
 */
void Communication::unpackageBytesInBuf(int *value, int posB1, const char *rcvBuf)
{
    // TODO - can we reuse bitset classes save instantiating each time?
    std::bitset firstPos = std::bitset<8>(rcvBuf[posB1]);
    std::bitset secondPos = std::bitset<8>(rcvBuf[posB1 + 1]);
    std::bitset result = std::bitset<16>(firstPos.to_ulong() << firstPos.size() | secondPos.to_ulong());

    *value = static_cast<int>(result.to_ulong());
}

/*
 * Packages an integer value into two bytes and inserts them into a char buffer
 *
 * @param value the int value to be converted into bytes
 * @param posB1 the position in the buffer where the two bytes should be inserted
 * @param sendBuf pointer to the char buffer which is going to be sent to the client/server
 */
void Communication::packageBytesInBuf(int value, int posB1, char *sendBuf)
{
    std::bitset valueToBitset = std::bitset<16>(value);

    char b1 = 0;
    char b2 = 0;
    int i;

    for (i = 15; i >= 0; i--)
    {
        if (i > 7)
        {
            b1 <<= 1;
            b1 |= valueToBitset[i];
        }
        else
        {
            b2 <<= 1;
            b2 |= valueToBitset[i];
        }
    }

    // convert it to byte
    stringStream << std::hex << b1;
    stringStream.str("");
    stringStream << std::hex << b2;
    stringStream.str("");

    sendBuf[posB1] = b1;
    sendBuf[posB1 + 1] = b2;
}
