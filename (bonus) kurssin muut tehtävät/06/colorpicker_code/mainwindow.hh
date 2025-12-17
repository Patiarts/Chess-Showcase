#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

// #include "sliderspinboxpair.hh"
// #include "colorrectwidget.hh"
#include <QMainWindow>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void set_color();

private:
    const int RGB_MAX = 255;

    // SliderSpinBoxPair* reds_;
    // SliderSpinBoxPair* greens_;
    // SliderSpinBoxPair* blues_;
    // ColorRectWidget* color_rect_;

    QSlider* reds_;
    QSlider* greens_;
    QSlider* blues_;
    QLabel* col_label_;

};
#endif // MAINWINDOW_HH
