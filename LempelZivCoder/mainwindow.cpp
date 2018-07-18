#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QVector>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    QWidget::setWindowTitle("Encoder");
    QWidget::setWindowIcon(QIcon(":/img/icon.png"));
    QWidget::setMaximumSize(300, 300);
    QWidget::setMinimumSize(300, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_press_clicked()
{
    if(fileName.length() == 0){
         QMessageBox::information(this, "Error","Enter Path");
         return;
    }
    ///
    QString newFile;
    for(int j = 0; j < fileName.length(); j++){
        if(j == fileName.length() - 4){
          newFile+="_Press.txt";
          break;
        }
        newFile+= fileName[j];
    }
    //////////////////////////////////////////////////////
    //QFile file(fileName);
    QFile file("D:/file.txt");
    QFile fileOut(newFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(this, "Error 404","Not found");
        return;
    }
    else
        ui->output->setText(fileName);
    if(!fileOut.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, "Error","Error");
         return;
    }
    //////////////////////////////////////////////////////
    QTextStream  in(&file);
    QVector<symb> ar;
    QString data;
        while (!in.atEnd()){
            data += in.read(1)[0];
        }
        ui->progressBar->setValue(0);
        ui->progressBar->setMaximum(data.length() - 2);
        ui->progressBar->setMinimum(0);
        for(int i = 0; i < data.length(); i++){
             ui->progressBar->setValue(i);
            int index = 0;
            QChar ch = data[i];
            QString str = data[i]+"";
            for(int j =  ar.length() - 1; j > 0 ; j--){
                if(sborForIndex(ar, j) == str){
                    index = j;
                    i++;
                    ch = data[i];
                    str += data[i]+"";
                    //j = ar.length() - 1;
                }
            }
            if(index){
              ar.push_back(symb(index, ch));
            }
            else
              ar.push_back(symb(0, ch));

        }
        ar.push_back(symb(0, ' '));

    //////////////////////////////////////////////////////
    QTextStream sin(&fileOut);
    for(int i = 0; i < ar.length(); i++)
            sin  <<   ar[i].i << ar[i].s;
    sin  <<  " ";
    //////////////////////////////////////////////////////
    fileOut.close();
    file.close();
}

void MainWindow::on_depress_clicked()
{
    if(fileName.length() == 0){
         QMessageBox::information(this, "Error","Enter Path");
         return;
    }

    ///
    QString newFile;
    for(int j = 0; j < fileName.length(); j++){
        if(j == fileName.length() - 4){
          newFile+="_De.txt";
          break;
        }
        newFile+= fileName[j];
    }
    //////////////////////////////////////////////////////
    //QFile file(fileName);
    QFile file("D:/file_Press.txt");
    QFile fileOut(newFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(this, "Error 404","Not found");
    else
        ui->output->setText(fileName);
    if(!fileOut.open(QIODevice::WriteOnly))
        QMessageBox::information(this, "Error","Error");
    //////////////////////////////////////////////////////
    QTextStream  in(&file);
    QVector<symb> ar;
    QString data;
    QString dataNumber;
    bool push = true;
    QChar s = in.read(1)[0];
    while (!in.atEnd()){
        s = in.read(1)[0];
        if(s.isNumber()){
            if(push){
                ar.push_back(symb(dataNumber.toInt(), data[0]));
                data = "";
                dataNumber = "";
            }
           dataNumber += s;
           push = false;
        }
        else{
            data += s;
            push = true;
        }
    }
    data = "";
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(data.length() - 2);
    ui->progressBar->setMinimum(0);
    for(int i = 0; i < ar.length(); i++){
         ui->progressBar->setValue(i + 1);
            if(ar[i].i == 0)
               data+= ar[i].s;
            else{
               data+= sborForIndex(ar, i);
            }

        }

    //////////////////////////////////////////////////////
    QTextStream sin(&fileOut);
    sin << data;
    sin << " ";

    //////////////////////////////////////////////////////
    fileOut.close();
    file.close();
}


QString MainWindow::sborForIndex(QVector<symb> vec, int i){
    QString secStr = vec[i].s;
    while(true){
        i = vec[i].i;
        if(i>0)
           secStr += vec[i].s;
        else
            break;
    }
    QString str;
    for(int i = 0, j = secStr.length()-1 ; j >=0; i++, j--){
        str[i] = secStr[j];
    }
    return str;
}


void MainWindow::on_Directory_clicked()
{
    QString file = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "D://",
                "Text File (*.txt)"
                );
    fileName = file;
    ui->output->setText(file);
}


