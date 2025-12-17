/*
 * COMP.CS.155 : 9.5 Shakki : pieceimage.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 */

#include "pieceimage.hh"

QRgb PieceImage::white_color = 0xffffffff;
QRgb PieceImage::white_shade = 0xe0e0e0e0;
QRgb PieceImage::black_color = 0xff555555;
QRgb PieceImage::black_shade = 0xff3c3c3c;

PieceImage::PieceImage(const QString& filename)
    : QImage(32, 32, QImage::Format_Indexed8)
    , piece_window_({0,0,32,32})
{
    QImage::load(filename);
    QImage::setColorTable(INIT_COLORS);
}

void PieceImage::set_white_colors(QRgb main, QRgb shade)
{
    PieceImage::white_color = main;
    PieceImage::white_shade = shade;
}

void PieceImage::set_black_colors(QRgb main, QRgb shade)
{
    PieceImage::black_color = main;
    PieceImage::black_shade = shade;
}

void PieceImage::set_displayed_piece(const std::shared_ptr<ChessPiece> piece_ptr)
{
    // if input piece doesnt exist, set piece window to spot EMPTY (0).
    if(piece_ptr == nullptr){
        set_piece_window(EMPTY);
        return;
    }
    // otherwise, set piece window to reflect the type of piece.
    PieceType piece_type = piece_ptr->get_type();
    set_piece_window(piece_type);

    // then, change colors to match the piece as well
    ChessColor piece_color = piece_ptr->get_color();
    if(piece_color == WHITE){
        set_to_white();
    }
    else{
        set_to_black();
    }
}


void PieceImage::highlight(HighlightMode mode)
{
    // By default, image is not highlighted, which means the
    // secondary outline in the piece sprites should be transparent.
    QRgb hl_color = TRANSPARENT;

    // If PieceImage is highlighted somehow, choose the appropriate color.
    // Selected pieces should be highlighted with white,
    // and captureable (if empty, moveable) should be red.
    switch(mode){
        case NONE: break;
        case SELECTION: hl_color = WHITE_HIGHLIGHT; break;
        case MOVEABLE: hl_color = RED_HIGHLIGHT; break;
    }

    // Setting the QImage color palette to the chosen color at index HIGHLIGHT.
    QImage::setColor(HIGHLIGHT, hl_color);
}

QRect PieceImage::piece_window() const
{
    return piece_window_;
}

void PieceImage::set_to_white()
{
    QImage::setColor(MAIN_COLOR, PieceImage::white_color);
    QImage::setColor(SHADE_COLOR, PieceImage::white_shade);
}

void PieceImage::set_to_black()
{
    QImage::setColor(MAIN_COLOR, PieceImage::black_color);
    QImage::setColor(SHADE_COLOR, PieceImage::black_shade);
}

void PieceImage::set_piece_window(PieceType to_piece)
{
    // parameter to_piece is an enum, which can helpfully be used to multiply PIECE_IMG_SIZE.
    // This is why the order of the PieceType enum is important; it has to match the order
    // of the pieces in the pieces.png image.

    // In pieces.png, the different piece type sprites are each contained in a 32x32 pixel region.
    // by multiplying PIECE_IMG_SIZE=32 with the to_piece enum, the piece_window_ is shifted to
    // contain exactly the correct piece sprite.
    piece_window_ = QRect{to_piece * PIECE_IMG_SIZE, 0, PIECE_IMG_SIZE, PIECE_IMG_SIZE};
}

void PieceImage::set_color(ChessColor color)
{
    if(color == WHITE){set_to_white();}
    else{set_to_black();}
}


