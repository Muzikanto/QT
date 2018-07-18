#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindowing.h"
#include <cmath>
#include <QPushButton>
#include "sizeform.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum Esize{
        small,medium,large, dynamic
    };
    enum Eview{
        standart, ingeneer, programming
    };

    QSize sizeStandart;
    QSize sizeSmallStandart;
    QSize sizeLargeStandart;
    QSize sizeDynamycStandart;

    Esize size;
    Eview view;
    int fractionLen = 8;

    double value1;
    QString znak;
    int arrButtonsLen = 1;
    QPushButton **arrButtons = new QPushButton* [1]{};



private slots:
    void digits_numbers();
    void operations();
    void Math_Operations();
    void on_calcButtonEqual_clicked();

    void setNewArrQPushBut(int);
    void createButton(QString str, int index, QString layout, QString slot);
    void deleteButtons();

    void on_NavCalcStandartt_triggered();
    void on_NavcalcIngForm_triggered();
    void on_NavcalcProgForm_triggered();
    QString operatTo2(int);
    QString operat2To10(int);
    void removeIngForm();
    void removeProgForm();

    void resetIcon();
    void checkSize();
    void setSize(QSize);

    void on_SmallForm_triggered();
    void on_MediumForm_triggered();
    void on_LargeForm_triggered();
    void on_DynamycSizeForm_triggered();

    void setDynamycSizeForm(int, int);

    void on_NavExitCalc_triggered();



    void on_Maxim_triggered();

signals:
    void getSizeData(QSize);

private:
    Ui::MainWindow *ui;
    SizeForm *window;


};

#endif // MAINWINDOW_H
