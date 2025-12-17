#include "bishop.hh"

/*
 * COMP.CS.155 : 9.5 Shakki : bishop.cpp
 * Modifier: Patrik Reitkivi
 * stud.num: 151106280
 *
 * Implemented get_allowed_moves.
*/

Bishop::Bishop(ChessColor col): ChessPiece(col, BISHOP, "bishop")
{}

set<Coord> Bishop::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> legals = {};

    // Check diagonals for legal moves.
    check_moves_in_dir(board, legals, UP_RIGHT);
    check_moves_in_dir(board, legals, DOWN_RIGHT);
    check_moves_in_dir(board, legals, DOWN_LEFT);
    check_moves_in_dir(board, legals, UP_LEFT);

    return legals;
}
