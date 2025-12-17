/*
COMP.CS.115 : 5.5 Polku : gameboard.hh
Tehtävän tekijä: Patrik Reitkivi
Op.num: 151106280
*/

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <string>
#include <memory>

// Pelilaudan ulottuvuusvakioita
const int ROWS = 5;
const int COLUMNS = 4;
const int BOARD_SIZE = ROWS * COLUMNS;

// Lautamerkkivakiot
const char OUT_OF_BOUNDS = ' ';
const char FREE_SPACE = 'o';
const char GREEN_PIECE = 'G';
const char RED_PIECE = 'R';

// Apuvakioita tulostukseen
const char PRINTOUT_UPPER_BLOCK[16 * 3] = "===============\n"
                                          "|   | 1 2 3 4 |\n"
                                          "---------------";
const char PRINTOUT_BOTTOM_LINE[16] = "===============";

const char INITIAL_BOARD_SETUP[BOARD_SIZE +1] = "GGGG o   oo  o  RRRR";
const char SOLVED_BOARD_STATE[BOARD_SIZE +1] = "RRRR o   oo  o  GGGG";


struct Point{
    int x;
    int y;

    bool operator==(const Point& other) const{
        return x == other.x && y == other.y;
    }
    // bool operator!=(const Point& other) const{
    //     return x != other.x || y != other.y;
    // }
    // void operator=(const Point& other){
    //     x = other.x;
    //     y = other.y;
    // } olisin mieluusti lisännyt kaikki tarpeettomatkin operaattorit
    Point operator+(const Point& other) const{
        return {x + other.x, y + other.y};
    }
    Point operator-(const Point& other) const{
        return {x - other.x, y - other.y};
    }
};

// Reitinlöytöön käytettyjä "suuntavakioita". Käytännössä
// yksikkövektoreita.          YLÖS   ALAS   VASEN   OIKEA
const Point DIRECTIONS[4] = { {0,-1}, {0,1}, {-1,0}, {1,0} };


class GameBoard
{
public:
    // Rakentaja
    GameBoard();

    // Purkaja
    virtual ~GameBoard();

    // Selittämättömiä metodeja. Alkuperä tuntematon.
    std::string get_board() const;
    char get_at(const Point &p) const; // heittää range_errorin jos indeksipiste ei ole sopivalla alueella.
    char get_at(const int x, const int y) const;

    // Täyttää laudan alustavasti: vihreät nappulat asetetaan yläriville,
    // punaista alariville, ja muut paikat ovat tyhjiä.
    void initial_fill();

    // Täyttää laudan juuri niinkuin käytäjä haluaa.
    // Ainoat rajoitukset ovat, että merkkimäärä on oikea (BOARD_SIZE),
    // ja että käytetään vain sallittuja merkkejä (lautamerkkivakiot).
    // Pelin ratkeavuuden toteutumista ei tarkisteta;
    // tämä on tarkoitettu lähinnä yksikkötesteille.
    // (Luokkaa voitaisiin täydentää niin, että se tallentaa myös
    // custom_solved_board-merkkijonon?)
    bool custom_setup(std::string setup);

    // Printsaa Gameboardin.
    void print() const;

    // Palauttaa tosi jos peli on ohi, siis jos vihreät nappulat ovat alarivillä
    // ja punaiset ylärivillä.
    bool is_game_over() const;

    // Tarkistaa annettujen pisteiden laillisuuden. Ollakseen laillinen, syötteen
    // molempien pisteiden on kuuluttava laudan sisällä käytettyihin pisteisiin,
    // alkupisteessä on oltava nappula, ja loppupisteen on oltava tyhjä.
    // (Implisiittisesti tarkistaa, etteivät annetut pisteet ole samat.)
    // Palauttaa tosi, jos annetut pisteet täyttävät kriteerit.
    bool are_valid_points(const Point& start,
                       const Point& destination) const;

    // Jos mahdollista, siirtää nappulan alkupisteestä loppupisteeseen.
    // Palauttaa tosi, jos pisteiden välinen polku löytyy.
    bool move(const Point& start, const Point& destination);

private:
    // Tietue rekursiivisen pathfind_fromto-metodin käyttöön.
    // Path_elementeistä syntyy dynaaminen pino, joka tallentaa
    // siihen asti tutkitun polun muodon (ehkä vähän tarpeetonta).
    struct Path_elem{
        Point pos;
        std::shared_ptr<Path_elem> prev;
    };

    // Syöteparametreina Path-elem-pinon huippu sekä maalikentän koordinaatit.
    // Etsii rekursiivisesti, onko viimeisimmän askeleen (from) ja maalin (destination) välillä avointa polkua.
    // Avoin polku koostuu vapaista, ortagonaalisesti vierekkäisistä kentistä, joka alkaa from-kentästä
    // ja loppuu destination-kenttään (alkukenttä sisältää nappulan).
    // Tämänhetkinen toteutus mahdollistaa vaikka löytyneen polun tulostuksen, koska Path_elem-pino
    // tallentaa sen kokonaisuudessaan.
    bool pathfind_fromto(const std::shared_ptr<Path_elem> from, const Point& destination) const;

    // Muuntaa pisteen koordinaatit indeksiksi lautamerkkijonoon.
    // Palauttaa tuloksen.
    // ptobix == point_to_board_index. Lyhyt näppäryyden vuoksi. (eikä kuulu julkiseen rajapintaan hehheh)
    int ptobix(const Point& p) const;
    int ptobix(const int x,const int y) const;

    bool point_in_bounds(const Point& p) const;
    bool point_in_bounds(const int x, const int y) const;

    std::string board_;
};

#endif // GAMEBOARD_HH
