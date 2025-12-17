#include "king.hh"

/*
 * COMP.CS.155 : 9.5 Shakki : king.cpp
 * Modifier: Patrik Reitkivi
 * stud.num: 151106280
 *
 * Implemented get_allowed_moves.
*/

King::King(ChessColor col): ChessPiece(col, KING, "king")
{}

set<Coord> King::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> legals = {};
    Coord pos = get_position();
    ChessColor own_color = get_color();
    std::shared_ptr<ChessPiece> piece_ptr = nullptr;

    // The king's range of movement are the eight surrounding squares.
    // Check all those for legality.
    for(const Coord dir : {UP, UP_RIGHT, RIGHT, DOWN_RIGHT,
                            DOWN, DOWN_LEFT, LEFT, UP_LEFT}){

        Coord spot = pos + dir;
        // of course, OOB spots are not legal moves.
        if(!board.coord_in_bounds(spot)){continue;}

        // A spot is legal, if it is empty or contains an enemy piece.
        piece_ptr = board.get_piece_at(spot);
        if(piece_ptr == nullptr || piece_ptr->get_color() != own_color){ // or-operator seems to short-circuit, but is this good practice? idk.
            legals.insert(spot);
        }
    }

    return legals;
}
