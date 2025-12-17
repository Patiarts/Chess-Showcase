#ifndef CHESSSQUAREWIDGET_HH
#define CHESSSQUAREWIDGET_HH

/*
 * COMP.CS.155 : 9.5 Shakki : chesssquarewidget.hh
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * A custom QWidget for displaying and controlling the chess gameplay.
 * Each ChessSquareWidget displays a flat rectangle (chess square), as well as a chess piece
 * graphic on top (PieceImage).
 *
 * A ChessSquareWidget can be in one of three HighlightModes (defined in pieceimage.hh).
 * Each highlight mode corresponds to a graphical highlighting behavior;
 * NONE - Normal, no highlight.
 * SELECTION - Only squares with a piece can be in this mode. The piece gets a white outline.
 * MOVEABLE - Empty squares draw a red circle, and otherwise the contained piece gets a red outline.
 *
 * The widget is also an input widget, reating to mouse clicks. These inputs are used to
 * control the chess game (the logic itself is handled mainly in MainWindow).
 * The widget also reacts (graphically) to mouse hovering, changing color when the cursor is over it.
 *
 * This widget used to contain some attempts at resizing logic, but that has now been delegated to
 * BoardWidget.
*/

#include "chesspiece.hh"
#include "pieceimage.hh"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <memory>

class ChessSquareWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChessSquareWidget(QWidget *parent = nullptr, ChessColor color = WHITE, Coord coord = NULL_COORD);

    // Static methods for controlling the color scheme of the chess squares.
    static void set_white_colors(QRgb base, QRgb hover);
    static void set_black_colors(QRgb base, QRgb hover);

    // Setter for the piece_ptr_ variable.
    void set_piece(std::shared_ptr<ChessPiece> new_piece_ptr);

    // Sets the hl_mode_ of the square to SELECTION.
    void select();
    bool is_selected() const;
    bool is_moveable() const;

    // Getters for coord and piece
    Coord coord() const;
    std::shared_ptr<ChessPiece> piece() const;

public slots:
    // QEvent handlers for highlighting squares appropriately.
    // Enter and Leave events control hovering behavior.
    // MousePress selects this square and notifies mainwindow about it.
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);

    // Slot to set all ChessSquareWidgets to NONE-highlight.
    void deselect(ChessSquareWidget* exception = nullptr);

    // Slot to set all ChessSquareWidgets, that are designated in legals, to MOVEABLE-highlight.
    void on_legals_announced(std::set<Coord> legals);

signals:
    // Emitted when ChessSquareWidget receives a mouse click.
    void clicked_on(ChessSquareWidget* self);

private:
    const float PIECE_SIZE_RATIO = 0.94; // 0.94 = 32/34. Creates a "1-pixel margin" around piece 32-pixel piece (including highlight)).

    // (Re)implementations of drawing.
    void paintEvent(QPaintEvent *event);
    void draw_piece(QPainter& painter, QPaintEvent *e);

    // private setter for hl_mode_. Also sets piece_img_ highlight mode.
    void change_hl_mode(HighlightMode next);

    // Static color scheme variables. All squares share this color
    // scheme, but it is also variable (hence static instead of const)
    static QRgb base_col_w_;
    static QRgb hover_col_w_;
    static QRgb base_col_b_;
    static QRgb hover_col_b_;

    // color_ decides what color to draw square as.
    ChessColor color_;
    // coord_ is used to interface with the logic of the chess game.
    Coord coord_;

    // hl_mode_ is used both to designate graphical style (highlight outlines), as well as
    // for designating ChessSquareWidgets as legal destinations for a chess move.
    HighlightMode hl_mode_;
    bool hovered_;

    // piece_img_ to easily draw a chess sprite on top of the square.
    PieceImage piece_img_;
    // piece_ptr_ is a pointer to the chess piece object that currently occupies
    // a ChessSquareWidget.
    std::shared_ptr<ChessPiece> piece_ptr_;
};

#endif // CHESSSQUAREWIDGET_HH
