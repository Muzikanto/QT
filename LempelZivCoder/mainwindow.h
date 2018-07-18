#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class symb{
public:
    symb(){};
    symb(int i, QChar s){
        this->i = i;
        this->s = s;
    }
    int i;
    QChar s;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fileName;
    QString sborForIndex(QVector<symb> vec, int i);
private slots:
    void on_press_clicked();
    void on_Directory_clicked();

    void on_depress_clicked();

private:
    Ui::MainWindow *ui;
};





#endif // MAINWINDOW_H
