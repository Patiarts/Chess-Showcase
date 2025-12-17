#include "sudoku.hh"
#include <iostream>

Sudoku::Sudoku()
{
    for(unsigned int i = 0; i<SIZE*SIZE; i++){
        _board = EMPTY_BOARD;
    }
}

bool Sudoku::set(int i, int j, char c)
{
    if(!is_in_bounds(i,j)){
        std::cout << "Trying to access illegal cell "
                  << coord(i,j) << "!" << std::endl;
        return false;
    }
    if(!is_legal_char(c)){
        std::cout << "Trying to set illegal character " << c
                  << " to " << coord(i,j) << "!" << std::endl;
        return false;
    }
    _board[bix(i,j)] = c;
    return true;
}

bool Sudoku::check()
{
    char fail = ' ';
    unsigned int i = 0;
    for(i = 0; i < SIZE; i++){
        if(!is_legal_segment(row(i), &fail)){
            std::cout << "Row " << i << " has multiple " << fail << "'s!" << std::endl;
            return false;
        }
    }
    for(i = 0; i < SIZE; i++){
        if(!is_legal_segment(col(i), &fail)){
            std::cout << "Column " << i << " has multiple " << fail << "'s!" << std::endl;
            return false;
        }
    }
    for(i = 0; i < SIZE; i++){
        int y = i/BLOCK_SIZE * BLOCK_SIZE;
        int x = i%BLOCK_SIZE * BLOCK_SIZE;
        if(!is_legal_segment(box(x,y), &fail)){
            std::cout << "Block at " << coord(y,x) << " has multiple " << fail << "'s!" << std::endl;
            return false;
        }
    }
    return true;
}

void Sudoku::print()
{
    for(unsigned int i = 0; i < SIZE; i++){
        if(i%3 == 0){std::cout << THICK_LINE << std::endl;}
        else{std::cout << THIN_LINE << std::endl;}
        std::cout << row_printout(i) << std::endl;
    }
    std::cout << THICK_LINE << std::endl;
    return;
}

char Sudoku::cell(int i, int j)
{
    return _board[bix(i,j)];
}

str Sudoku::row(int i)
{
    return _board.substr(SIZE*i, SIZE);
}

str Sudoku::col(int j)
{
    str coli = "         ";
    for(unsigned int i = 0; i < SIZE; i++){
        coli[i] = cell(i,j);
    }
    return coli;
}

str Sudoku::box(int i, int j)
{
    str boxij = "";
    size_t start = bix(i,j);
    boxij += _board.substr(start, BLOCK_SIZE);
    boxij += _board.substr(start+SIZE, BLOCK_SIZE);
    boxij += _board.substr(start+2*SIZE, BLOCK_SIZE);
    return boxij;
}

bool Sudoku::is_in_bounds(int i, int j)
{
    return !(i < 0 || j < 0 || i >= int(SIZE) || j >= int(SIZE));
}

bool Sudoku::is_legal_char(char c)
{
    return c == EMPTY || SYMBOLS.find(c) != str::npos;
}

bool Sudoku::is_legal_segment(str seg, char *fail)
{
    for(unsigned int i = 0; i < SIZE; i++){
        int char_count = 0;
        for(unsigned int j = 0; j < SIZE; j++){
            char_count += int(seg[j] == SYMBOLS[i]);
            if(char_count > 1){
                *fail = SYMBOLS[i];
                return false;
            }
        }
    }
    return true;
}

str Sudoku::coord(int i, int j)
{
    return "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
}

str Sudoku::row_printout(int i)
{
    str data = row(i);
    str to_print = "";
    for(unsigned int k = 0; k < SIZE; k++){
        if(k%3 == 0){to_print += "# ";}
        else{to_print += "| ";}
        to_print.push_back(data[k]);
        to_print += " ";
    }
    to_print.push_back('#');
    return to_print;
}

void Sudoku::printraw()
{
    for(unsigned int i = 0; i < SIZE; i++){
        std::cout << row(i) << std::endl;
    }
    return;
}

size_t Sudoku::bix(int i, int j)
{
    return SIZE*i + j;
}






