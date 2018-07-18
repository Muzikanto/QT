#ifndef SIZEFORM_H
#define SIZEFORM_H

#include <QDialog>

namespace Ui {
    class SizeForm;
}

class SizeForm : public QDialog
{
    Q_OBJECT

public:
    explicit SizeForm(QSize v, QWidget *parent = 0);
    ~SizeForm();
    int width;
    int height;
    QSize size;

signals:
    void getSizeForm(int, int);

private slots:
    void setWidth(int);
    void setHeight(int);




private:
    Ui::SizeForm *ui;
};

#endif // SIZEFORM_H
