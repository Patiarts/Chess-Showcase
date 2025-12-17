#include "chesssquarewidget.hh"

// Pedefining static variables to some default colors.
QRgb ChessSquareWidget::base_col_w_ = QColor("light grey").rgb();
QRgb ChessSquareWidget::hover_col_w_ = QColor("grey").rgb();
QRgb ChessSquareWidget::base_col_b_ = QColor("dark grey").rgb();
QRgb ChessSquareWidget::hover_col_b_ = QColor("grey").rgb();

ChessSquareWidget::ChessSquareWidget(QWidget *parent, ChessColor color, Coord coord)
    : QWidget(parent)
    , color_(color)
    , coord_(coord)
    , hl_mode_(NONE)
    , hovered_(false)
    , piece_img_(PieceImage(":/pieces/pieces.png"))
    , piece_ptr_(nullptr)
{
    // Make widget react to mouse movements over it
    setAttribute(Qt::WA_Hover, true);
}

void ChessSquareWidget::set_white_colors(QRgb base, QRgb hover)
{
    base_col_w_ = base;
    hover_col_w_ = hover;
}

void ChessSquareWidget::set_black_colors(QRgb base, QRgb hover)
{
    base_col_b_ = base;
    hover_col_b_ = hover;
}

void ChessSquareWidget::set_piece(std::shared_ptr<ChessPiece> new_piece_ptr)
{
    piece_ptr_ = new_piece_ptr;
    update();
}

void ChessSquareWidget::select()
{
    hl_mode_ = SELECTION;
    update();
}

bool ChessSquareWidget::is_selected() const
{
    return hl_mode_ == SELECTION;
}

bool ChessSquareWidget::is_moveable() const
{
    return hl_mode_ == MOVEABLE;
}

Coord ChessSquareWidget::coord() const
{
    return coord_;
}

std::shared_ptr<ChessPiece> ChessSquareWidget::piece() const
{
    return piece_ptr_;
}

void ChessSquareWidget::enterEvent(QEvent*)
{
    hovered_ = true;
}

void ChessSquareWidget::leaveEvent(QEvent*)
{
    hovered_ = false;
}

void ChessSquareWidget::mousePressEvent(QMouseEvent *)
{
    if(hl_mode_ == MOVEABLE){
        // Do none of the following
    }
    else if(piece_ptr_ == nullptr){
        // empty squares shouldn't be selectable.
        change_hl_mode(NONE);
    }
    else{
        change_hl_mode(SELECTION);
    }
    // even if square was not selected, it still counts as deselecting other squares. So
    // clicked_on is emitted.
    emit clicked_on(this);
    update();
}

void ChessSquareWidget::deselect(ChessSquareWidget *exception)
{
    // exception exists so that newly selected squares are not immediately deselected.
    if(this != exception){
        change_hl_mode(NONE);
        update();
    }
}

void ChessSquareWidget::on_legals_announced(std::set<Coord> legals)
{
    if(hl_mode_ == SELECTION){
        return;
    }
    if(legals.find(coord_) == legals.end()){
        change_hl_mode(NONE);
        return;
    }
    change_hl_mode(MOVEABLE);
}

void ChessSquareWidget::paintEvent(QPaintEvent *event)
{
    // First, define a QPainter for graphical happenings.
    // Then, decide painted color based on hl_mode_ and hovered_.
    // Finally, paint.

    QPainter painter = QPainter(this);

    //QRgb painted_color = 0xffff00ff;
    // if(color_ == BLACK){
    //     painted_color = hovered_? hover_col_b_ : base_col_b_;
    // }
    // else{
    //     painted_color = hovered_? hover_col_w_ : base_col_w_;
    // }

    // This is silly, as well as equivalent with the commented code above
    QRgb painted_color =
        (color_)?
            hovered_? hover_col_b_ : base_col_b_ :
            hovered_? hover_col_w_ : base_col_w_ ;

    painter.fillRect(event->rect(), painted_color);
    draw_piece(painter, event);
}

void ChessSquareWidget::draw_piece(QPainter &painter, QPaintEvent *e)
{
    // Finding the smaller of the "square" dimensions
    int w = e->rect().width();
    int h = e->rect().height();
    int min_dim = (w < h)? w : h;

    // piece_rect designates the area where painter should paint the piece_img_.
    // min_dim was found so that this can be a square.
    QRect piece_rect(0,0, min_dim * PIECE_SIZE_RATIO, min_dim * PIECE_SIZE_RATIO);
    piece_rect.moveCenter(e->rect().center());

    // Set the piece_img_ to display the correct chess piece, and then draw it.
    piece_img_.set_displayed_piece(piece_ptr_);
    painter.drawImage(piece_rect, piece_img_, piece_img_.piece_window());
}

void ChessSquareWidget::change_hl_mode(HighlightMode next)
{
    piece_img_.highlight(next);
    hl_mode_ = next;
}
