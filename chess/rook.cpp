#include "rook.hh"

/*
 * COMP.CS.155 : 9.5 Shakki : rook.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * Implemented get_allowed_moves
 */

Rook::Rook(ChessColor col): ChessPiece(col, ROOK, "rook"){}

set<Coord> Rook::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> legals = {};

    // The rook can move up, down, left and right. Check those directions
    // for legal moves.
    check_moves_in_dir(board, legals, UP);
    check_moves_in_dir(board, legals, RIGHT);
    check_moves_in_dir(board, legals, DOWN);
    check_moves_in_dir(board, legals, LEFT);

    return legals;
}
