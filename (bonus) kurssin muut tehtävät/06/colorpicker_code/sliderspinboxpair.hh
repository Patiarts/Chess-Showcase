#ifndef SLIDERSPINBOXPAIR_HH
#define SLIDERSPINBOXPAIR_HH

#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

class SliderSpinBoxPair : public QWidget
{
    Q_OBJECT
public:
    explicit SliderSpinBoxPair(QWidget *parent = nullptr);
    ~SliderSpinBoxPair();

    int min() const;
    int max() const;
    void set_min(int new_min);
    void set_max(int new_max);

    int value() const;

    QHBoxLayout& layout() const;
    QSlider& slider() const;
    QSpinBox& spinbox() const;
signals:
    int value_changed(int to);
private slots:
    void on_value_changed(int to);
private:
    int min_ = 0;
    int max_ = 100;

    QHBoxLayout* layout_;
    QSlider* slider_;
    QSpinBox* spinbox_;
};

#endif // SLIDERSPINBOXPAIR_HH
