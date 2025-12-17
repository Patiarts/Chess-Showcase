#include "basegame.hh"
#include <iostream>

BaseGame::BaseGame(unsigned int rounds) : rounds_(rounds)
{
    setPlayers("player1", "player2");
}

BaseGame::~BaseGame()
{

}

void BaseGame::setPlayers(const std::string &name1, const std::string &name2)
{
    player1_ = {name1, 0};
    player2_ = {name2, 0};
}

void BaseGame::play()
{
    printGameName();
    for(unsigned int i = 0; i < rounds_; ++i)
    {
        std::cout << "Round " << i + 1 << std::endl;
        std::string answer1 = askInput(player1_);
        std::string answer2 = askInput(player2_);
        unsigned int winner = roundWinner(answer1, answer2);
        if(winner == P1_WIN)
        {
            ++player1_.wins;
            std::cout << "  " << player1_.name << " won" << std::endl;
        }
        else if(winner == P2_WIN)
        {
            ++player2_.wins;
            std::cout << "  " << player2_.name << " won" << std::endl;
        }
        else
        {
            std::cout << "  It's a tie " << winner << std::endl;
        }
    }
    reportResult();
}

std::string BaseGame::askInput(const Player &player) const
{
    std::string answer = "";
    std::cout << "  " << player.name << ": ";
    std::cin >> answer;
    return answer;
}

void BaseGame::printGameName() const
{
    std::cout << "Word game" << std::endl;
}

RESULT BaseGame::roundWinner(const std::string& word1,
                                   const std::string& word2) const
{
    //std::cout << "BaseGame::roundWinner" << std::endl;
    if(word1.size() > word2.size())
    {
        return P1_WIN;
    }
    else if(word1.size() < word2.size())
    {
        return P2_WIN;
    }
    else
    {
        return DRAW;
    }
}

void BaseGame::reportResult() const
{
    std::cout << "Game over" << std::endl;
    std::cout << "  " << player1_.name << ": " << player1_.wins << std::endl;
    std::cout << "  " << player2_.name << ": " << player2_.wins << std::endl;
}

