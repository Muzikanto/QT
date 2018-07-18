#include "mainwindowing.h"
#include "ui_mainwindowing.h"



MainWindowIng::MainWindowIng(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowIng)
{
    ui->setupUi(this);
}

MainWindowIng::~MainWindowIng()
{
    delete ui;
}

void MainWindowIng::on_navStandartCalc_triggered()
{
   
}

void MainWindowIng::on_NavExit_triggered()
{
    QApplication::quit();
}
