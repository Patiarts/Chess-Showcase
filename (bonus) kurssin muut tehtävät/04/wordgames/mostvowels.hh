#ifndef MOSTVOWELS_H
#define MOSTVOWELS_H

#include "basegame.hh"


class MostVowels: public BaseGame
{
public:
    MostVowels(unsigned int rounds);
    virtual ~MostVowels();

private:
    const unsigned int VOWEL_COUNT = 6;
    const char VOWELS[6] = {'a','i','e','o','u','y'};

    RESULT roundWinner(const std::string& word1, const std::string& word2) const;

    void printGameName() const;
};

#endif // MOSTVOWELS_H
