#include "sizeform.h"
#include "ui_sizeform.h"
#include <QDebug>

SizeForm::SizeForm(QSize value, QWidget *parent) :  QDialog(parent),ui(new Ui::SizeForm)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Main Form Sizing");
    QWidget::setWindowIcon(QIcon(":/img/icon.png"));
    size = value;
    ui->spinBoxWidth->setMaximum(500);
    ui->spinBoxHeight->setMaximum(600);
    ui->horizontalSliderWidth->setMaximum(500);
    ui->horizontalSliderHeight->setMaximum(600);
    ui->spinBoxWidth->setMinimum(200);
    ui->spinBoxHeight->setMinimum(280);
    ui->horizontalSliderWidth->setMinimum(200);
    ui->horizontalSliderHeight->setMinimum(280);
    width = value.width();
    height= value.height();
    ui->spinBoxWidth->setValue(width);
    ui->spinBoxHeight->setValue(height);
    ui->horizontalSliderWidth->setValue(width);
    ui->horizontalSliderHeight->setValue(height);

    connect(ui->spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(setWidth(int)));
    connect(ui->horizontalSliderWidth, SIGNAL(valueChanged(int)), this, SLOT(setWidth(int)));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(setHeight(int)));
    connect(ui->horizontalSliderHeight, SIGNAL(valueChanged(int)), this, SLOT(setHeight(int)));
    QWidget::setMinimumSize(QSize(341,214));
    QWidget::setMaximumSize(QSize(341,214));
}



void SizeForm::setWidth(int a){
    width = a;
    ui->spinBoxWidth->setValue(a);
    ui->horizontalSliderWidth->setValue(a);
    emit getSizeForm(width, height);
}

void SizeForm::setHeight(int a){
    height = a;
    ui->spinBoxHeight->setValue(a);
    ui->horizontalSliderHeight->setValue(a);
    emit getSizeForm(width, height);
}

SizeForm::~SizeForm()
{
    delete ui;
}

