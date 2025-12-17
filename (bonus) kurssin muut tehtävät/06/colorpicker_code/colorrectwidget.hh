#ifndef COLORRECTWIDGET_HH
#define COLORRECTWIDGET_HH

#include <QWidget>
#include <QColor>

class ColorRectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorRectWidget(QWidget *parent = nullptr);
    QColor color();
    QColor inverse();
public slots:
    void change_color(const QColor to);

signals:
    void color_changed(QColor to);
protected:
    virtual void paintEvent(QPaintEvent*);
private:
    QColor color_;
    QColor inverse_;
};

#endif // COLORRECTWIDGET_HH
