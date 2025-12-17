#ifndef ROCKPAPERSCISSORS_HH
#define ROCKPAPERSCISSORS_HH

#include "basegame.hh"

enum RPS_PLAY{NOT_A_RPS, ROCK, PAPER, SCISSORS};

class RockPaperScissors : public BaseGame
{
public:
    RockPaperScissors(unsigned int rounds);
    virtual ~RockPaperScissors();
private:

                               // P1 plays: NOT_A_RPS   ROCK        PAPER       SCISSORS |  P2 plays:
    const RESULT RPS_RESULT_TABLE[4][4] = {{DRAW,       P1_WIN,     P1_WIN,     P1_WIN}, // NOT_A_RPS
                                           {P2_WIN,     DRAW,       P1_WIN,     P2_WIN}, // ROCK
                                           {P2_WIN,     P2_WIN,     DRAW,       P1_WIN}, // PAPER
                                           {P2_WIN,     P1_WIN,     P2_WIN,     DRAW }}; // SCISSORS


    RESULT roundWinner(const std::string& word1, const std::string& word2) const;

    void printGameName() const;

    RPS_PLAY stringToPlay(const std::string& input) const;
};

#endif // ROCKPAPERSCISSORS_HH
