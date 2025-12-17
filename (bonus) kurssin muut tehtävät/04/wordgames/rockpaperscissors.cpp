#include "rockpaperscissors.hh"
#include <iostream>

RockPaperScissors::RockPaperScissors(unsigned int rounds): BaseGame(rounds) {}

RockPaperScissors::~RockPaperScissors() {}

RESULT RockPaperScissors::roundWinner(const std::string &word1, const std::string &word2) const
{
    RPS_PLAY play1 = stringToPlay(word1);
    RPS_PLAY play2 = stringToPlay(word2);
    return RPS_RESULT_TABLE[play2][play1];
}

void RockPaperScissors::printGameName() const
{
    std::cout << "Rock-Paper-Scissors Game" << std::endl;
}

RPS_PLAY RockPaperScissors::stringToPlay(const std::string& input) const
{
    std::string uppered = input;
    for(size_t i = 0; i < uppered.size(); i++){
        uppered[i] = std::toupper(uppered[i]);
    }

    if(uppered == "ROCK"){
        return ROCK;
    }
    if(uppered == "PAPER"){
        return PAPER;
    }
    if(uppered == "SCISSORS"){
        return SCISSORS;
    }
    return NOT_A_RPS;
}
