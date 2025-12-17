#include "mostvowels.hh"
#include <iostream>

MostVowels::MostVowels(unsigned int rounds): BaseGame(rounds) {}

MostVowels::~MostVowels() {}

RESULT MostVowels::roundWinner(const std::string &word1, const std::string &word2) const
{
    unsigned int vowelc_1 = 0;
    unsigned int vowelc_2 = 0;

    unsigned int i = 0;
    unsigned int j = 0;

    for(i = 0; i < VOWEL_COUNT; i++){

        for(j = 0; j < word1.size(); j++){
            if(word1[j] == VOWELS[i]){
                vowelc_1++;
                continue;
            }
        }

        for(j = 0; j < word2.size(); j++){
            if(word2[j] == VOWELS[i]){
                vowelc_2++;
                continue;
            }
        }
    }

    if(vowelc_1 > vowelc_2){
        return P1_WIN;
    }
    if(vowelc_2 > vowelc_1){
        return P2_WIN;
    }
    return DRAW;
}

void MostVowels::printGameName() const
{
    std::cout << "Most Vowels Game" << std::endl;
}
