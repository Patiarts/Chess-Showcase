#ifndef BOARDWIDGET_HH
#define BOARDWIDGET_HH

/*
 * COMP.CS.115 : 9.5 Shakki : boardwidget.hh
 * Author: Patrik Reitkivi
 * St.num: 151106280
 *
 * Header file for custom widget BoardWidget.
 * Its purpose is to display the rim of the Chesboard, as well as
 * keep the graphics and especially its layout's contents square.
*/

#include <QLabel>
#include <QResizeEvent>

class BoardWidget : public QLabel
{
    Q_OBJECT
public:
    BoardWidget(QWidget* parent);

    // changes between flipped and unflipped board picture.
    void flip_image();

    // Some square-keeping methods.
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    // Overridden QLabel resizeEvent method calls the
    // private methods resize_image and resize_layout.
    void resizeEvent(QResizeEvent *e);

private:
    // Self-explanatory constants
    const QString SOURCE_FILENAME = ":/pieces/board.png";
    const QString FLIPPED_FILENAME = ":/pieces/board_flipped.png";
    const QSize MIN_SIZE = {340,340};   // board png size is 340x340
    const float LAYOUT_MARGIN_RATIO = 0.2;  // Ratio of margin to full size board pixmap, to nicely center layout

    // These methods handle the custom resizing-logic of this widget,
    // keeping it all nice and square.
    void resize_image(QResizeEvent* e);
    void resize_layout(QResizeEvent* e);

    // Storing the pixmaps might be a bit unnecesary, but i thought it would technically be faster
    // than re-opening the input files. The pixmap shown on the label itself
    // cannot be used, as it is distorted when resizing the image.
    QPixmap board_pixmap_;
    QPixmap flipped_pixmap_;
    bool is_flipped_;
};

#endif // BOARDWIDGET_HH
