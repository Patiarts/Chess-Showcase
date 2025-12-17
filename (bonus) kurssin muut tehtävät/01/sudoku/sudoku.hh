#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <string>

typedef std::string str;

// Sizes of a block and the whole sudoku
const unsigned int BLOCK_SIZE = 3;
const unsigned int SIZE = 3 * BLOCK_SIZE;
// Valid symbols for sudoku
const char EMPTY = ' ';
const str SYMBOLS = "123456789";
// other useful strings
const str EMPTY_BOARD = "                                                                                 ";
const str THICK_LINE = "#####################################";
const str THIN_LINE = "#---+---+---#---+---+---#---+---+---#";

class Sudoku
{
public:
    Sudoku();
    bool set(int i, int j, char c);
    bool check();
    void print();
private:
    // getters for cells, rows, cols and boxes.
    char cell(int i, int j);
    str row(int i);
    str col(int j);
    str box(int i, int j);
    // checks for validity. is_legal_segment "returns" first erroneous char.
    bool is_in_bounds(int i, int j);
    bool is_legal_char(char c);
    bool is_legal_segment(str seg, char *fail);
    // print assistant methods
    str coord(int i, int j);
    str row_printout(int i);
    // debug methods
    void printraw();
    // Coordinate to _board index
    size_t bix(int i, int j);

    // The board is here defined as an array of chars; a string.
    // every 9th element is considered to be in the same column.
    str _board;
};

#endif // SUDOKU_HH








