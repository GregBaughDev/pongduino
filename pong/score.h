#ifndef SCORE_H
#define SCORE_H

class Score
{
public:
    Score() : player1Score(0), player2Score(0){};
    void incrementPlayer(int player);
    void displayScore();
private:
    int player1Score;
    int player2Score;
};

#endif
