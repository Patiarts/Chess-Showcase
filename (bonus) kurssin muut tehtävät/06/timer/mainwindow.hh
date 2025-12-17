#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_timer_timeout();
    void on_start_released();
    void on_stop_released();
    void on_reset_released();

private:
    void increment_secs();
    void increment_mins();
    void increment_hour();

    int sec_ = 0;
    int min_ = 0;
    int hour_ = 0;

    int remaining_msec = 1000;

    Ui::MainWindow *ui;
    QTimer *timer_;
};
#endif // MAINWINDOW_HH
