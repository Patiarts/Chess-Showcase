/*
COMP.CS.115 : 5.5 Polku : gameboard.cpp
Tehtävän tekijä: Patrik Reitkivi
Op.num: 151106280
*/

#include <iostream>
#include "gameboard.hh"

GameBoard::GameBoard() {}

GameBoard::~GameBoard() {}

std::string GameBoard::get_board() const
{
    return board_;
}

char GameBoard::get_at(const Point &p) const
{
    if (!point_in_bounds(p)){
        throw std::range_error("board get index out of bounds");
    }
    return board_[ptobix(p)];
}

char GameBoard::get_at(const int x, const int y) const
{
    if (!point_in_bounds(x,y)){
        throw std::range_error("board get index out of bounds");
    }
    return board_[ptobix(x,y)];
}

void GameBoard::initial_fill()
{
    board_ = INITIAL_BOARD_SETUP;
}

bool GameBoard::custom_setup(std::string setup)
{
    if (setup.size() != BOARD_SIZE){
        return false;
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        bool is_oob = (setup[i] == OUT_OF_BOUNDS);
        bool is_free = (setup[i] == FREE_SPACE);
        bool is_green = (setup[i] == GREEN_PIECE);
        bool is_red = (setup[i] == RED_PIECE);
        if ( !(is_oob || is_free || is_green || is_red)){
            return false;
        }
    }

    board_ = setup;
    return true;
}

void GameBoard::print() const
{
    std::cout << PRINTOUT_UPPER_BLOCK << std::endl; // laudan muuttumaton yläreuna

    for(unsigned int i = 0; i < ROWS; i++){

        std::cout << "| " << i+1 << " | "; // Numeroitujen rivien alku

        for(unsigned int j = 0; j < COLUMNS; j++){  // rivien sisältö
            std::cout << board_[ptobix(j, i)] << " ";
        }

        std::cout << "|" << std::endl;
    }

    std::cout << PRINTOUT_BOTTOM_LINE << std::endl; // laudan muuttumaton alareuna
}

bool GameBoard::is_game_over() const
{
    return board_ == SOLVED_BOARD_STATE;
}

bool GameBoard::are_valid_points(const Point &start, const Point &destination) const
{
    // Ovatko pisteet laudan sisällä?
    if (!point_in_bounds(start) || !point_in_bounds(destination)){
        return false;
    }

    int start_index = ptobix(start);
    int desti_index = ptobix(destination);

    // Mitä pisteistä löytyy?
    if (board_[start_index] != GREEN_PIECE && board_[start_index] != RED_PIECE){
        return false; // Aloituspiste ei ole nappula
    }
    if (board_[desti_index] != FREE_SPACE){
        return false; // Määränpää ei ole vapaana
    }

    return true;
}

bool GameBoard::move(const Point &start, const Point &destination)
{
    // Luodaan Path_elem-pinon ensimmäinen alkio.
    std::shared_ptr<Path_elem> pathfind_first_step = std::make_shared<Path_elem>(Path_elem{start, nullptr});
    // Rekursiivinen pathfind_fromto selvittää, onko syötekenttien välillä avointa polkua.
    if (!pathfind_fromto(pathfind_first_step, destination)){
        return false;
    }
    // Jos on, vaihdetaan pisteiden merkkien paikat laudassa.
    int start_ix = ptobix(start);
    int desti_ix = ptobix(destination);

    char tmp = board_[start_ix];
    board_[start_ix] = board_[desti_ix];
    board_[desti_ix] = tmp;

    return true;
}

bool GameBoard::pathfind_fromto(const std::shared_ptr<Path_elem> from, const Point &destination) const
{
    Point position = from->pos;

    // Rekursion perustapaus: maalissa ollaan jo
    if (position == destination){
        return true;
    }

    // Jos tutkittu piste ei ole vapaa, tämä suunta ei toimi ja palautetaan false.
    if (!point_in_bounds(position)){
        return false;
    }
    // Ensimmäinen piste on poikkeus: se saa olla varattu alunperin.
    if (from->prev != nullptr && get_at(position) != FREE_SPACE){
        return false;
    }
    /* Tämänhetkinen toteutus ei ymmärrä silmukoita. Jos laudassa olisi silmukka/kierros, jota voi kiertää,
       Tämä algoritmi voisi jäädä siihen jumiin. Jos tarve nousisi, tämän voisi ratkaista esim. asettamalla
       käytyihin ruutuihin tilapäinen "tutkittu"-merkki, jonka olemassaolo sitten estäisi myöhemmät käynnit. */

    Point backwards = {0,0};
    if (from->prev != nullptr){
        backwards = from->prev->pos - position;
    }

    // Tutkitaan rekursiivisesti lähtöpisteen naapurisuunnat.
    // Vältetään palaamasta takaisin samaan suuntaan.
    for(const Point dir : DIRECTIONS){
        Point next_direction = position + dir;
        if (dir == backwards){
            continue;
        }
        // Jos maali löytyy jostain suunnasta, hurraa! Polku on olemassa.
        std::shared_ptr<Path_elem> next_step = std::make_shared<Path_elem>(Path_elem{next_direction, from});
        if (pathfind_fromto(next_step, destination)){
            return true;
        }
    }

    // Jos mistään suunnasta ei löydy polkua,
    return false;
}

int GameBoard::ptobix(const Point &p) const
{
    return COLUMNS * p.y + p.x;
}

int GameBoard::ptobix(const int x, const int y) const
{
    return COLUMNS * y + x;
}

bool GameBoard::point_in_bounds(const Point &p) const
{
    bool is_in_bounds = (p.x >= 0 && p.x < COLUMNS && p.y >= 0 && p.y < ROWS);
    return is_in_bounds;
}

bool GameBoard::point_in_bounds(const int x, const int y) const
{
    bool is_in_bounds = (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS);
    return is_in_bounds;
}
