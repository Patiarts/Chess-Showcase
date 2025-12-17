#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton, &QPushButton::released, this, &MainWindow::calculateBmiEvent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateBmiEvent()
{
    QString weight_str = ui->weightLineEdit->text();
    QString height_str = ui->heightLineEdit->text();

    bool is_float = false;
    float weight_kg = weight_str.toFloat(&is_float);
    if(!is_float){
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->clear();
        return;
    }

    float height_cm = height_str.toFloat(&is_float);
    if(!is_float){
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->clear();
        return;
    }

    if(height_cm == 0){
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->clear();
        return;
    }
    float height_m = height_cm/100;

    float bmi = weight_kg/(height_m * height_m);
    QString bmi_str = QString::number(bmi);

    ui->resultLabel->setText(bmi_str);
    if(bmi < 18.5){
        ui->infoTextBrowser->setText("Underweight");
    }
    else if(bmi > 25){
        ui->infoTextBrowser->setText("Overweight");
    }
    else{

        ui->infoTextBrowser->setText("Normal range");
    }
}
