#include "colorrectwidget.hh"
#include <QPainter>

ColorRectWidget::ColorRectWidget(QWidget *parent)
    : QWidget{parent}
    , color_(QColor("Black"))
    , inverse_(QColor("White"))
{}

QColor ColorRectWidget::color()
{
    return color_;
}

QColor ColorRectWidget::inverse()
{
    return inverse_;
}

void ColorRectWidget::change_color(const QColor to)
{
    color_ = to;

    int inv_red = 255 - to.red();
    int inv_gre = 255 - to.green();
    int inv_blu = 255 - to.blue();
    inverse_ = QColor(inv_red, inv_gre, inv_blu);

    update();
    emit color_changed(color_);
}

void ColorRectWidget::paintEvent(QPaintEvent *)
{
    QPainter bruh(this);
    int w = this->geometry().width();
    int h = this->geometry().height();
    bruh.fillRect(0,0,w,h, color_);
    QPen newpen = QPen();
    newpen.setWidth(16);
    newpen.setColor(inverse_);
    bruh.setPen(newpen);
    bruh.drawRect(0,0,w,h);
}
