/*
STUDENT: DO NOT MODIFY THIS FILE!
*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/*
 * COMP.CS.155 : 9.5 Shakki : chessboard.hh
 * Modifier: Patrik Reitkivi
 * stud.num: 151106280
 *
 * modifications marked with "M!"
*/

#include <array>
#include <memory>
#include <climits>


using namespace std;


/**
 * @brief The Coord class
 * Represents a two dimensional coordinate.
 */
struct Coord
{
    int row;
    int col;

    // Comparison operators
    bool operator== (const Coord &other) const {
        return row == other.row && col == other.col;
    }
    bool operator!= (const Coord &other) const {
        return !(*this == other);
    }
    bool operator< (const Coord &other) const {
        return row < other.row || (row == other.row && col < other.col);
    }

    // M! Sum operators have been added for convenience in finding legal moves
    Coord operator+ (const Coord &other) const {
        return {row + other.row, col + other.col};
    }

    void operator+= (const Coord &other) {
        row += other.row, col += other.col;
    }
};

// M! Defining useful direction constants for utility. NULL_COORD was
// Changed from base code. It seems to be used for "taking pieces off the board";
// its value itself seems irrelevant. It used to be {-1,-1}, which is now DOWN_LEFT.
const Coord NULL_COORD = {INT_MIN, INT_MIN};
const Coord UP          = { 1,  0};
const Coord UP_RIGHT    = { 1,  1};
const Coord RIGHT       = { 0,  1};
const Coord DOWN_RIGHT  = {-1,  1};
const Coord DOWN        = {-1,  0};
const Coord DOWN_LEFT   = {-1, -1};
const Coord LEFT        = { 0, -1};
const Coord UP_LEFT     = { 1, -1};


// Forward declaration of ChessPiece because ChessBoard and ChessPiece depend on each other
class ChessPiece;

const int BOARD_SIZE = 8;

// Board data structure. A two dimensional array of shared pointers to ChessPieces.
using Board = array<array<shared_ptr<ChessPiece>, BOARD_SIZE>, BOARD_SIZE>;

/**
 * @brief The ChessBoard class
 * Represents a chess board. It is responsible for keeping track of the pieces on the board.
 */
class ChessBoard
{
public:
    ChessBoard();

    /**
     * @brief get_piece_at Gets the piece at a given coordinate if one exists there.
     * @param c the coord
     * @return the piece at the coord if there is one, nullptr otherwise. Out of bounds coords
     * return nullptr as well.
     */
    shared_ptr<ChessPiece> get_piece_at(Coord const& c) const;
    shared_ptr<ChessPiece> get_piece_at(int row, int col) const;



    /**
     * @brief coord_in_bounds checks if a coord is within the bounds of the chess board
     * @param c the coord to check
     * @return true if the coord is in bounds, false otherwise
     */
    bool coord_in_bounds(Coord const& c) const;

    /**
     * @brief set_piece Sets the piece at the given coordinates. Do not use for moving pieces, only for
     * setting new pieces onto the board.
     * @param row
     * @param col
     * @param piece
     * @return true if piece was set, false otherwise
     */
    bool set_piece(int row, int col, shared_ptr<ChessPiece> piece);
    bool set_piece(Coord coord, shared_ptr<ChessPiece> piece);

private:
    Board board_;
};

#endif // CHESSBOARD_H
