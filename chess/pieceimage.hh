#ifndef PIECEIMAGE_HH
#define PIECEIMAGE_HH

/*
 * COMP.CS.155 : 9.5 Shakki : pieceimage.hh
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * Custom QImage child descendant class to simplify drawing chess pieces with appropriate highlights.
 * Built specifically with 32x32 indexed pixel sprites in mind, with a very limited color palette.
 *
 * This class is an image of all chess pieces (including "empty piece"). It also controls the colors
 * of the piece(s), including two different ways of highlighting them.
 * Used in ChessSquareWidget.
 *
 * Color changes (which includes highlighting) are achieved by using the QImage classes
 * capacity to use an indexed image type and color palettes.
 * Displaying a specific piece type works by defining a piece_window_ region and using it when drawing.
*/

#include "chesspiece.hh"
#include <memory.h>
#include <QImage>
#include <QList>

// Enum for controlling the highlighting behavior of the image, as well as
// gameplay input logic in ChessSquareWidget.
enum HighlightMode{NONE, SELECTION, MOVEABLE};

class PieceImage : public QImage
{
public:
    PieceImage(const QString& filename);

    // Control the color scheme of all PieceImages
    static void set_white_colors(QRgb main, QRgb shade);
    static void set_black_colors(QRgb main, QRgb shade);

    // control the displayed piece type and color of a specific Pieceimage.
    // set_displayed_piece does both,
    void set_displayed_piece(const std::shared_ptr<ChessPiece> piece_ptr);
    // set_piece_window selects only the piece type,
    void set_piece_window(PieceType to_piece);
    // and set_color changes only the color.
    void set_color(ChessColor color);

    // change highlighting behavior of the sprite
    void highlight(HighlightMode mode = NONE);

    // piece_window_ getter
    QRect piece_window() const;

private:
    // Define indices of colors used by sprite. Changing the color palette at index OUTLINE,
    // for example, would make the black outline of the piece be not black.
    // Only MAIN_COLOR and SHADE_COLOR are intended to change.
    enum PieceColorInx{BACKGROUND, OUTLINE, MAIN_COLOR, SHADE_COLOR, HIGHLIGHT};
    const int PIECE_IMG_SIZE = 32;

    // Defining non-variable common colors as well as initial default colors.
    const QRgb WHITE_HIGHLIGHT = 0xffffffff;
    const QRgb RED_HIGHLIGHT = 0xffff0000;
    const QRgb TRANSPARENT = 0x00000000;
    const QVector<QRgb> INIT_COLORS = {TRANSPARENT,    // Transparent background
                                       0xff000000,    // Black outline
                                       0xffffffff,    // main color of piece
                                       0xf0f0f0f0,    // secondary color (shadow)
                                       TRANSPARENT};   // Secondary outline for highlights

    // Static colors to make all PieceImages share the same, variable color palette.
    static QRgb white_color;
    static QRgb white_shade;
    static QRgb black_color;
    static QRgb black_shade;

    // Set this piece to follow either white or black color scheme (change inx MAIN_COLOR and SHADE_COLOR in color palette).
    void set_to_white();
    void set_to_black();

    // Stores which piece is "chosen" currently.
    // QPainter has a method drawImage, which asks for a region of the
    // source image that is intended to be drawn. piece_image_ is the
    // intended drawn region of PieceImage.
    QRect piece_window_;
};

#endif // PIECEIMAGE_HH
