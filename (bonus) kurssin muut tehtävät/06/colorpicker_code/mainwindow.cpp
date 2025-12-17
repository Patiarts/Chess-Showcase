#include "mainwindow.hh"
#include <QLayout>
#include <QSpinBox>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , reds_(new SliderSpinBoxPair(this))
//     , greens_(new SliderSpinBoxPair(this))
//     , blues_(new SliderSpinBoxPair(this))
//     , color_rect_(new ColorRectWidget(this))
// {
//     QVBoxLayout* vlayout = new QVBoxLayout(this);
//     vlayout->addWidget(reds_,1);
//     vlayout->addWidget(greens_,1);
//     vlayout->addWidget(blues_,1);

//     QHBoxLayout* hlayout = new QHBoxLayout(this);
//     hlayout->addLayout(vlayout, 3);
//     hlayout->addWidget(color_rect_, 1);

//     QWidget* central_container = new QWidget(this);
//     setCentralWidget(central_container);
//     central_container->setLayout(hlayout);

//     resize(400, 100);

//     connect(reds_, &SliderSpinBoxPair::value_changed, this, &MainWindow::set_color);
//     connect(greens_, &SliderSpinBoxPair::value_changed, this, &MainWindow::set_color);
//     connect(blues_, &SliderSpinBoxPair::value_changed, this, &MainWindow::set_color);

//     reds_->set_max(RGB_MAX);
//     greens_->set_max(RGB_MAX);
//     blues_->set_max(RGB_MAX);

//     reds_->slider().setObjectName("horizontalSliderRed");
//     greens_->slider().setObjectName("horizontalSliderGreen");
//     blues_->slider().setObjectName("horizontalSliderBlue");

//     reds_->spinbox().setObjectName("spinBoxRed");
//     greens_->spinbox().setObjectName("spinBoxGreen");
//     blues_->spinbox().setObjectName("spinBoxBlue");

// }

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , reds_(new QSlider(this))
        , greens_(new QSlider(this))
        , blues_(new QSlider(this))
        , col_label_(new QLabel(this))
    {
        reds_->setOrientation(Qt::Horizontal);
        greens_->setOrientation(Qt::Horizontal);
        blues_->setOrientation(Qt::Horizontal);

        QSpinBox* red_spin = new QSpinBox(this);
        QSpinBox* green_spin = new QSpinBox(this);
        QSpinBox* blue_spin = new QSpinBox(this);

        reds_->setMaximum(RGB_MAX);
        greens_->setMaximum(RGB_MAX);
        blues_->setMaximum(RGB_MAX);

        red_spin->setMaximum(RGB_MAX);
        green_spin->setMaximum(RGB_MAX);
        blue_spin->setMaximum(RGB_MAX);

        reds_->setObjectName("horizontalSliderRed");
        greens_->setObjectName("horizontalSliderGreen");
        blues_->setObjectName("horizontalSliderBlue");

        red_spin->setObjectName("spinBoxRed");
        green_spin->setObjectName("spinBoxGreen");
        blue_spin->setObjectName("spinBoxBlue");

        connect(reds_, &QSlider::valueChanged, this, &MainWindow::set_color);
        connect(greens_, &QSlider::valueChanged, this, &MainWindow::set_color);
        connect(blues_, &QSlider::valueChanged, this, &MainWindow::set_color);

        connect(reds_, &QSlider::valueChanged, red_spin, &QSpinBox::setValue);
        connect(greens_, &QSlider::valueChanged, green_spin, &QSpinBox::setValue);
        connect(blues_, &QSlider::valueChanged, blue_spin, &QSpinBox::setValue);

        connect(red_spin, QOverload<int>::of(&QSpinBox::valueChanged), reds_, &QSlider::setValue);
        connect(green_spin, QOverload<int>::of(&QSpinBox::valueChanged), greens_, &QSlider::setValue);
        connect(blue_spin, QOverload<int>::of(&QSpinBox::valueChanged), blues_, &QSlider::setValue);

        QGridLayout* grid = new QGridLayout(this);

        grid->addWidget(reds_, 0, 0);
        grid->addWidget(greens_, 1, 0);
        grid->addWidget(blues_, 2, 0);

        grid->addWidget(red_spin, 0, 1);
        grid->addWidget(green_spin, 1, 1);
        grid->addWidget(blue_spin, 2, 1);

        grid->addWidget(col_label_, 0, 2, 3, 1);
        col_label_->update();

        grid->setColumnStretch(0,3);
        grid->setColumnStretch(1,1);
        grid->setColumnStretch(2,1);

        QWidget* central_container = new QWidget(this);
        setCentralWidget(central_container);
        central_container->setLayout(grid);

        set_color();
        adjustSize();
}

MainWindow::~MainWindow() {}

void MainWindow::set_color()
{
    QColor selectedColor(reds_->value(),
                         greens_->value(),
                         blues_->value());

    QPixmap colorMap(128,128);
    colorMap.fill(selectedColor);
    col_label_->setPixmap(colorMap);
}

// void MainWindow::set_color()
// {
//     int r = reds_->value();
//     int g = greens_->value();
//     int b = blues_->value();
//     QColor next_color(r,g,b);
//     color_rect_->change_color(next_color);
// }
