/*
STUDENT: DO NOT MODIFY THIS FILE!
*/

#include "chesspiece.hh"

/*
 * COMP.CS.155 : 9.5 Shakki : chesspiece.cpp
 * Modifier: Patrik Reitkivi
 * stud.num: 151106280
 *
 * Implemented new method, check_moves_in_dir
*/

ChessPiece::ChessPiece(ChessColor color, PieceType type, string name): color_(color), type_(type), name_(name) {}

ChessColor ChessPiece::get_color() const
{
    return color_;
}

PieceType ChessPiece::get_type() const
{
    return type_;
}

Coord ChessPiece::get_position() const
{
    return position_;
}

void ChessPiece::set_position(Coord pos)
{
    position_ = pos;
}

// Although not all chess pieces use this, half of them do. It made more sense
// to put this as a method in the abstract chess piece class than to separately implement it thrice.
void ChessPiece::check_moves_in_dir(const ChessBoard &board, set<Coord> &legals, const Coord& direction) const
{
    Coord check_spot = get_position() + direction;
    ChessColor own_color = get_color();
    std::shared_ptr<ChessPiece> piece_ptr = nullptr;

    // Keep checking spots in direction until no longer in bounds.
    while(board.coord_in_bounds(check_spot)){

        piece_ptr = board.get_piece_at(check_spot);
        // If empty spot, add it to legals and move on.
        if(piece_ptr == nullptr){
            legals.insert(check_spot);
            check_spot += direction;
            continue;
        }
        // If not empty, stop checking. Add opponent pieces to legals, for captures.
        else if(piece_ptr->get_color() != own_color){
            legals.insert(check_spot); 
        }
        return;
    }
}

string ChessPiece::get_name() const
{
    return name_;
}
