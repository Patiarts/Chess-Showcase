#include "queen.hh"

/*
 * COMP.CS.155 : 9.5 Shakki : queen.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * Implemented get_allowed_moves
 */

Queen::Queen(ChessColor col): ChessPiece(col, QUEEN, "queen")
{}

set<Coord> Queen::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> legals = {};

    // The queen can move in all 8 directions, so lets check them all!
    for(const Coord dir : {UP, UP_RIGHT, RIGHT, DOWN_RIGHT, // I wonder if this is good practice...
                            DOWN, DOWN_LEFT, LEFT, UP_LEFT}){
        check_moves_in_dir(board, legals, dir);
    }

    return legals;
}
