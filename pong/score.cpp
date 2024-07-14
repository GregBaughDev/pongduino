#include "score.h"
#include <raylib.h>
#include <string>

void Score::displayScore()
{
    DrawText(std::to_string(player1Score), 10, 100, 30, RAYWHITE);
}

void Score::incrementPlayer(int player)
{
    switch (player) {
        case 1:
            player1Score++;
            break;
        case 2:
            player2Score++;
            break;
    }
}

// conver the scores into char* using to_string and to_chars_result
// test credentials
