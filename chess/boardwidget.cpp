#include "boardwidget.hh"
#include <QLayout>
#include <cmath>

/*
 * COMP.CS.155 : 9.5 Shakki : boardwidget.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 */

BoardWidget::BoardWidget(QWidget* parent)
    : QLabel(parent)
    , board_pixmap_(SOURCE_FILENAME)
    , flipped_pixmap_(FLIPPED_FILENAME)
    , is_flipped_(false)
{
    setPixmap(board_pixmap_);
    setAlignment(Qt::AlignCenter);
}

void BoardWidget::flip_image()
{
    is_flipped_?
        setPixmap(board_pixmap_.scaled(size(), Qt::KeepAspectRatio)) :
        setPixmap(flipped_pixmap_.scaled(size(), Qt::KeepAspectRatio));
    is_flipped_ = !is_flipped_;

    update();
}

QSize BoardWidget::sizeHint() const
{
    int w = geometry().width();
    return QSize(w, w);
}

QSize BoardWidget::minimumSizeHint() const
{
    return MIN_SIZE;
}

// int BoardWidget::heightForWidth(int w) const
// {
//     return w;
// }

// bool BoardWidget::hasHeightForWidth() const
// {
//     return true;
// }

void BoardWidget::resizeEvent(QResizeEvent *e)
{
    resize_image(e);
    resize_layout(e);
}

void BoardWidget::resize_image(QResizeEvent* e)
{
    // Scale the pixmap image according to the smaller dimension of the widget.
    int w = e->size().width();
    int h = e->size().height();
    int min_dim = (w < h)? w : h;

    // This scaling is why storing the picture as a separate pixmap is necessary.
    // The pixmap displayed in the label is distorted by scaling, which would snowball
    // in recurring resizes.
    QPixmap scaled_pixmap = board_pixmap_.scaled(min_dim, min_dim, Qt::KeepAspectRatio);
    setPixmap(scaled_pixmap);
}

void BoardWidget::resize_layout(QResizeEvent *e)
{
    if(layout() == nullptr){
        return;
    }

    // The layout is centered by editing its contents margins.
    // This is done once again with the smaller dimension of the widget.
    // Margins are adjusted by the following math.
    // The resulting layout is niecly centered within the board rim image.
    float w = (float) e->size().width();
    float h = (float) e->size().height();
    float min_dim = (w < h)? w : h;

    float w_diff = w - min_dim;
    float h_diff = h - min_dim;

    float h_margin_f = (min_dim * LAYOUT_MARGIN_RATIO + w_diff) /2;
    float v_margin_f = (min_dim * LAYOUT_MARGIN_RATIO + h_diff) /2;

    int hori_margin = std::floor(h_margin_f);
    int vert_margin = std::floor(v_margin_f);

    layout()->setContentsMargins(hori_margin, vert_margin, hori_margin, vert_margin);
}
