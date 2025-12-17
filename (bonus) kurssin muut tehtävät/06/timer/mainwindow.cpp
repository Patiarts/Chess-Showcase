#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer_(new QTimer(this))
{
    ui->setupUi(this);

    timer_->setSingleShot(false);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::on_timer_timeout);

    connect(ui->startButton, &QPushButton::released, this, &MainWindow::on_start_released);
    connect(ui->stopButton, &QPushButton::released, this, &MainWindow::on_stop_released);
    connect(ui->resetButton, &QPushButton::released, this, &MainWindow::on_reset_released);
    connect(ui->closeButton, &QPushButton::released, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_timeout()
{
    timer_->setInterval(1000);
    increment_secs();
}

void MainWindow::on_start_released()
{
    if(timer_->isActive()){
        return;
    }
    timer_->start(remaining_msec);
}

void MainWindow::on_stop_released()
{
    remaining_msec = timer_->remainingTime();
    timer_->stop();
}

void MainWindow::on_reset_released()
{
    timer_->stop();
    remaining_msec = 1000;
    ui->lcdNumberHour->display(0);
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    sec_ = 0;
    min_ = 0;
    hour_ = 0;

}

void MainWindow::increment_secs()
{
    sec_++;
    if(sec_ >= 60){
        increment_mins();
        sec_ = 0;
    }
    ui->lcdNumberSec->display(sec_);
}

void MainWindow::increment_mins()
{
    min_++;
    if(min_ >= 60){
        increment_hour();
        min_ = 0;
    }
    ui->lcdNumberMin->display(min_);
}

void MainWindow::increment_hour()
{
    hour_++;
    ui->lcdNumberHour->display(hour_);
}
