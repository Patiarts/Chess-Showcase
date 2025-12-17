#include "sliderspinboxpair.hh"


SliderSpinBoxPair::SliderSpinBoxPair(QWidget *parent)
    : QWidget{parent}
    , layout_(new QHBoxLayout(this))
    , slider_(new QSlider(this))
    , spinbox_(new QSpinBox(this))
{
    set_min(0);
    set_max(99);

    slider_->setOrientation(Qt::Horizontal);
    layout_->addWidget(slider_, 7);
    layout_->addWidget(spinbox_, 1);

    connect(slider_, &QSlider::valueChanged, spinbox_, &QSpinBox::setValue);
    connect(spinbox_, QOverload<int>::of(&QSpinBox::valueChanged), slider_, &QSlider::setValue);
    connect(slider_, &QSlider::valueChanged, this, &SliderSpinBoxPair::on_value_changed);

    setLayout(layout_);
}

SliderSpinBoxPair::~SliderSpinBoxPair(){}

int SliderSpinBoxPair::min() const
{
    return min_;
}

int SliderSpinBoxPair::max() const
{
    return max_;
}

void SliderSpinBoxPair::set_min(int new_min)
{
    min_ = new_min;
    slider_->setMinimum(min_);
    spinbox_->setMinimum(min_);
}

void SliderSpinBoxPair::set_max(int new_max)
{
    max_ = new_max;
    slider_->setMaximum(max_);
    spinbox_->setMaximum(max_);
}

int SliderSpinBoxPair::value() const
{
    return slider_->value();
}

QHBoxLayout &SliderSpinBoxPair::layout() const
{
    return *layout_;
}

QSlider &SliderSpinBoxPair::slider() const
{
    return *slider_;
}

QSpinBox &SliderSpinBoxPair::spinbox() const
{
    return *spinbox_;
}

void SliderSpinBoxPair::on_value_changed(int to)
{
    emit value_changed(to);
}



