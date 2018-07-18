#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calcButton0,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->calcButton9,SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->calcButtonPlMn,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->calcButtonPerc,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->calcButtonComma,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->calcButtonDelete,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->calcClear,SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->calcButtonPlus,SIGNAL(clicked()), this, SLOT(Math_Operations()));
    connect(ui->calcButtonMinus,SIGNAL(clicked()), this, SLOT(Math_Operations()));
    connect(ui->calcButtonMult,SIGNAL(clicked()), this, SLOT(Math_Operations()));
    connect(ui->calcButtonDel,SIGNAL(clicked()), this, SLOT(Math_Operations()));


    QWidget::setWindowTitle("Calculator");
    QWidget::setWindowIcon(QIcon(":/img/icon.png"));
    ui->NavCalcStandartt->setIcon(QIcon(":/img/but.png"));
    ui->MediumForm->setIcon(QIcon(":/img/but.png"));
    ui->Maxim->setIcon(QIcon(":/img/admin.png"));

    size = Esize::medium;
    view = Eview::standart;
    sizeStandart = QSize(300, 400);
    sizeSmallStandart = QSize(200, 280);
    sizeLargeStandart = QSize(400, 500);
    sizeDynamycStandart = QSize(300, 400);
    checkSize();
    //QWidget::cursor()
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Operations
void MainWindow::digits_numbers(){

    QPushButton *button = (QPushButton *)sender();
    double numbers;
    QString newLabel;
    numbers = (ui->calcOut->text() + button->text()).toDouble();
    newLabel = QString::number(numbers, 'g', fractionLen);
    ui->calcOut->setText(newLabel);
}

QString MainWindow::operatTo2(int v){
    int numbersP = v;
    QString secLabel;
    QString a;
    for(;numbersP >=2;){
        secLabel += QString::number(numbersP%2, 'g', fractionLen);
        numbersP/=2;
    }
    if(numbersP == 1)
         secLabel += QString::number(1, 'g', fractionLen);
    for(int i = 0, j = secLabel.length() -1; i < secLabel.length(); j--, i++){
        a[i] = secLabel[j];
    }
    return a;
}
QString MainWindow::operat2To10(int v){
    int  len = ui->calcOut->text().length();
    QString str = QString::number(v, 'g', fractionLen);
    QString sec;
    int value = 0;
    for(int i = 0, j = len-1; i < len; i++, j--){
      sec =  str[i];
      value = value + (sec.toInt() * pow(2,j));
    }
    return QString::number(value, 'g', fractionLen);
}
void MainWindow::operations(){

    QPushButton *button = (QPushButton *)sender();
    double numbers;
    QString newLabel;
    numbers = (ui->calcOut->text()).toDouble();
    if(button->text() == "Clear"){
         znak = "";
         newLabel = "0";
         ui->calcOutOperator->setText("");
         ui->calcOutFirst->setText("");
    }
    if(button->text() == "<-"){
      QString str = ui->calcOut->text();
         for(int i = 0; i < str.length()-1;i++){
              newLabel[i] = str[i];
          }
          if(str.length() == 1)
              newLabel = "0";
    }
    else if(button->text() == "."){
       newLabel = QString::number(numbers, 'g', fractionLen);
       if(!ui->calcOut->text().contains('.'))
           newLabel = newLabel + '.';
    }
    else if(button->text() == "+/-"){
        newLabel = QString::number(-1 * numbers, 'g', fractionLen); }
    else if(button->text() == "%"){
        newLabel = QString::number(numbers * 0.01, 'g', fractionLen);

    }
    if(view == Eview::ingeneer){
        if(button->text() == "cos"){
         newLabel = QString::number(cos(numbers), 'g', fractionLen);
        }
        else if(button->text() == "sin"){
             newLabel = QString::number(sin(numbers), 'g', fractionLen);
        }
        else if(button->text() == "eLog"){
         newLabel = QString::number(log(numbers), 'g', fractionLen);
        }
        else if(button->text() == "xV2"){
           newLabel = QString::number(sqrt(numbers), 'g', fractionLen);
        }
        else if(button->text() == "x^2"){
           newLabel = QString::number(pow(numbers, 2), 'g', fractionLen);
        } else if(button->text() == "tan"){

           newLabel = QString::number(tan(numbers), 'g', fractionLen);
        } else if(button->text() == "exp"){
           newLabel = QString::number(exp(numbers), 'g', 8);
    }
}
    else if(view == Eview::programming){
        int numbersP = (int)numbers;
        QString secLabel;
        if(button->text() == "to2"){
           newLabel = operatTo2(numbersP);
        }
        else if(button->text() == "to8"){
            for(;numbersP >=8;){
                secLabel += QString::number(numbersP%8, 'g', fractionLen);
                numbersP/=8;
            }
            secLabel += QString::number(numbersP, 'g', fractionLen);
            for(int i = 0, j = secLabel.length() -1; i < secLabel.length(); j--, i++){
                newLabel[i] = secLabel[j];
            }
  }
        else if(button->text() == "to16"){
            int loc;
            for(;numbersP > 0;){
                if(numbersP - 16 >= 0)
                    loc = numbersP%16;
                else
                    loc = numbersP;
                QString symb;
                if(loc >= 10){
                if(loc == 15)
                    symb = "F";
                else if(loc == 14)
                    symb = "E";
                else if(loc == 13)
                    symb = "D";
                else if(loc == 12)
                    symb = "C";
                else if(loc == 11)
                    symb = "B";
                else if(loc == 10)
                    symb = "A";
                secLabel += symb;

                } else
                    secLabel += QString::number(loc, 'g', fractionLen);
                numbersP/=16;
                if(numbersP <=0)
                    break;
            }
           if(numbersP!=0)
            secLabel += QString::number(numbersP, 'g', fractionLen);
            for(int i = 0, j = secLabel.length() -1; i < secLabel.length(); j--, i++){
                newLabel[i] = secLabel[j];
            }
        }

        else if(button->text() == "fr2"){
            newLabel = operat2To10(numbersP);
        }
        else if(button->text() == "fr8"){
            int  len = ui->calcOut->text().length();
            QString str = ui->calcOut->text();
            QString sec;
            int value = 0;
            for(int i = 0, j = len-1; i < len; i++, j--){
              sec =  str[i];
              value = value + (sec.toInt() * pow(8,j));
            }
            newLabel = QString::number(value, 'g', fractionLen);
        }
        if(button->text() == "fr16"){
            int  len = ui->calcOut->text().length();
            QString str = ui->calcOut->text();
            QString sec;
            int value = 0;
            int secNum = 0;
            for(int i = 0, j = len-1; i < len; i++, j--){
              sec =  str[i];
              secNum = 0;
              if(sec == "F")
                  secNum = 15;
              else if(sec == "E")
                  secNum = 14;
              else if(sec == "D")
                  secNum = 13;
              else if(sec == "C")
                  secNum = 12;
              else if(sec == "B")
                  secNum = 11;
              else if(sec == "A")
                  secNum = 10;
              if(secNum)
                  value = value + (secNum * pow(16,j));
              else
                  value = value + (sec.toInt() * pow(16,j));
            }
            newLabel = QString::number(value, 'g', fractionLen);
        }
    }
    if(newLabel.length() == 0)
        newLabel = "0";
    ui->calcOut->setText(newLabel);
}

void MainWindow::Math_Operations(){
    QPushButton *button = (QPushButton *)sender();
    value1 = ui->calcOut->text().toDouble();
    ui->calcOut->setText("0");
    znak = button->text();
    ui->calcOutOperator->setText(button->text());
    ui->calcOutFirst->setText(QString::number(value1, 'g', fractionLen));
}

void MainWindow::on_calcButtonEqual_clicked()
{
    double labelNum = 0, numSec;
    QString newLabel;
    numSec = ui->calcOut->text().toDouble();

    if(znak=="+")
        labelNum = value1 + numSec;
     else if(znak=="-")
         labelNum = value1 - numSec;
     else if(znak=="*")
         labelNum = value1 * numSec;
     else if(znak=="/")
         labelNum = value1 / numSec;
    else if(view == Eview::ingeneer){
       if(znak=="x^y"){
            labelNum = pow(value1, numSec);
       } else if(znak=="xVy"){
            labelNum = pow(value1,  1/numSec);
       } else if(znak =="xlog"){
            labelNum = log10( value1 ) / log10( numSec );
       }
    }
    else if(view == Eview::programming){
        QString str1 =QString::number(value1,'g',fractionLen);
        QString str2 =QString::number(numSec,'g',fractionLen);
        QString newSt;
        if(str1[0] == '-'){
            for(int i = 0; i < str1.length()-1; i++){
                newSt[i] = str1[i];
            }
            str1 = newSt;
        }
        if(str2[0] == '-'){
            for(int i = 0; i < str2.length()-1; i++){
                newSt[i] = str2[i];
            }
             str1 = newSt;
        }

        int len;
        if(str1.length() > str2.length()){

            len = 1;
        }
        else{

            len = 2;
        }
        while(str1.length() != str2.length())
        {
            if(len == 2)
                str1 = "0" + str1;
            else
                str2 = "0" + str2;
        }
        if(znak=="(2)+"){
             str1 = operat2To10((int)value1);
             str2 = operat2To10((int)numSec);
             str1 = operatTo2(str1.toInt() + str2.toInt());
             labelNum = str1.toInt();
        }
        else  if(znak=="(2)-"){
            str1 = operat2To10((int)value1);
            str2 = operat2To10((int)numSec);
            int secInt = str1.toInt() - str2.toInt();
            if(secInt >=0)
                str1 = operatTo2(secInt);
            else
                str1 = operatTo2(-1*secInt);
            labelNum = str1.toInt();
        }
    }
    newLabel = QString::number(labelNum, 'g', fractionLen);
    znak = "";
    ui->calcOut->setText(newLabel);
    ui->calcOutOperator->setText("");
    ui->calcOutFirst->setText("");
    ui->statusBar->showMessage(newLabel);
}

//view calc
void MainWindow::on_NavCalcStandartt_triggered()
{

    if(view == Eview::ingeneer)
        removeIngForm();
    else if(view == Eview::programming)
        removeProgForm();
        checkSize();
}

void MainWindow::on_NavcalcIngForm_triggered()
{
   on_NavCalcStandartt_triggered();
   if(view != Eview::ingeneer){
    setNewArrQPushBut(10);
    createButton("x^2", 0, "layout1", "operator");
    createButton("x^y", 1, "layout1", "math");
    createButton("xV2", 2, "layout2", "operator");
    createButton("xVy", 3, "layout2", "math");
    createButton("sin", 4, "layout3", "operator");
    createButton("cos", 5, "layout4", "operator");
    createButton("xlog", 6, "layout3", "math");
    createButton("eLog", 7, "layout5", "operator");
    createButton("tan", 8, "layout4", "operator");
    createButton("exp", 9, "layout5", "operator");
    view = Eview::ingeneer;
    }
    checkSize();
}

void MainWindow::removeIngForm(){
    int i = 0;
    while(i < arrButtonsLen / 5){
        ui->horizontalLayout->removeWidget(arrButtons[i]);
        i++;
     }
    while(i < 2*arrButtonsLen / 5){
        ui->horizontalLayout_2->removeWidget(arrButtons[i]);
        i++;
     }
    while(i < 3*arrButtonsLen / 5){
        ui->horizontalLayout_3->removeWidget(arrButtons[i]);
        i++;
     }
    while(i < 4*arrButtonsLen / 5){
        ui->horizontalLayout_4->removeWidget(arrButtons[i]);
        i++;
     }
    while(i < 5*arrButtonsLen / 5){
        ui->horizontalLayout_5->removeWidget(arrButtons[i]);
        i++;
     }
     deleteButtons();
     view = Eview::standart;
}

void MainWindow::on_NavcalcProgForm_triggered()
{
    on_NavCalcStandartt_triggered();
    if(view != Eview::programming){
     setNewArrQPushBut(8);
     createButton("to2", 0, "progLay1", "operator");
     createButton("to8", 1, "progLay1", "operator");
     createButton("to16", 2, "progLay1", "operator");
     createButton("fr2", 3, "progLay2", "operator");
     createButton("fr8", 4, "progLay2", "operator");
     createButton("fr16", 5, "progLay2", "operator");
     createButton("(2)+", 6, "progLay1", "math");
     createButton("(2)-", 7, "progLay2", "math");
     view = Eview::programming;
    }
    checkSize();
}

void MainWindow::removeProgForm(){
    int i = 0;
    while(i < arrButtonsLen/2){
        ui->progLay1->removeWidget(arrButtons[i]);
        i++;
     }
    while(i < arrButtonsLen){
        ui->progLay2->removeWidget(arrButtons[i]);
        i++;
     }
     deleteButtons();
     view = Eview::standart;
}

//Buttons
void MainWindow::setNewArrQPushBut(int a){
    if(arrButtonsLen){
        delete[] arrButtons;
        arrButtons = new QPushButton* [a];
    }
    arrButtonsLen = a;
    for(int i = 0; i < arrButtonsLen; i++){
        arrButtons[i] = new QPushButton;
    }
}

void MainWindow::createButton(QString str, int index, QString layout, QString slot){
    arrButtons[index] = new QPushButton(this);
    arrButtons[index]->setText(str);
    if(layout == "layout1")
         ui->horizontalLayout->addWidget(arrButtons[index]);
     else if(layout == "layout2")
         ui->horizontalLayout_2->addWidget(arrButtons[index]);
     else if(layout == "layout3")
         ui->horizontalLayout_3->addWidget(arrButtons[index]);
     else if(layout == "layout4")
         ui->horizontalLayout_4->addWidget(arrButtons[index]);
     else if(layout == "layout5")
         ui->horizontalLayout_5->addWidget(arrButtons[index]);
     else if(layout == "progLay1")
         ui->progLay1->addWidget(arrButtons[index]);
    else if(layout == "progLay2")
         ui-> progLay2->addWidget(arrButtons[index]);
    if(slot == "operator"){
         connect(arrButtons[index], SIGNAL(clicked()), this, SLOT(operations()));
         arrButtons[index]->setStyleSheet("QPushButton {background-color: rgb(215, 215, 215);border: 1px solid gray;}QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #BEBEBE, stop: 1 #D7D7D7);}QPushButton::hover { border: 1px solid black;}");
    } else if(slot == "math") {
         connect(arrButtons[index], SIGNAL(clicked()), this, SLOT(Math_Operations()));
         arrButtons[index]->setStyleSheet("QPushButton {background-color: rgb(255, 151, 57);color: white; border: 1px solid gray;}QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FF7832, stop: 1 #FF9739);}QPushButton::hover { border: 1px solid black;}");

    }
    arrButtons[index]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    arrButtons[index]->setFont(QFont("Arial", 12,-1,false));
}

void MainWindow::deleteButtons(){
    for(int i = 0; i < arrButtonsLen; i++){
        delete arrButtons[i];
    }
}

void MainWindow::resetIcon(){
     ui->SmallForm->setIcon(QIcon());
      ui->MediumForm->setIcon(QIcon());
       ui->LargeForm->setIcon(QIcon());
        ui->DynamycSizeForm->setIcon(QIcon());
         ui->NavCalcStandartt->setIcon(QIcon());
          ui->NavcalcIngForm->setIcon(QIcon());
           ui->NavcalcProgForm->setIcon(QIcon());
}

//size
void MainWindow::checkSize (){
    resetIcon();
    if(size == Esize::small){
      setSize(sizeSmallStandart);
       ui->SmallForm->setIcon(QIcon(":/img/but.png"));
    }
    else if(size == Esize::medium){
       setSize(sizeStandart);
        ui->MediumForm->setIcon(QIcon(":/img/but.png"));
    }
    else if(size == Esize::large){
       setSize(sizeLargeStandart);
        ui->LargeForm->setIcon(QIcon(":/img/but.png"));
    }
    else if(size == Esize::dynamic){
       setSize(sizeDynamycStandart);
        ui->DynamycSizeForm->setIcon(QIcon(":/img/but.png"));
    }
}

void MainWindow::setSize(QSize Standart)
{
    if(view == Eview::standart){
    QWidget::setMinimumSize(Standart);
    QWidget::resize(Standart);
    QSize fix_size(Standart.width(), Standart.height());
    QWidget::setMaximumSize(fix_size);
    ui->NavCalcStandartt->setIcon(QIcon(":/img/but.png"));
    } else if(view == Eview::ingeneer) {
        QSize min_size(QSize(Standart.width() + Standart.width()/2, Standart.height()));
        QWidget::setMinimumSize(min_size);
        QWidget::resize(min_size);
        QSize fix_size(min_size.width(), min_size.height());
        QWidget::setMaximumSize(fix_size);
        ui->NavcalcIngForm->setIcon(QIcon(":/img/but.png"));
    } else if(view == Eview::programming) {
        QSize min_size(QSize(Standart.width(), Standart.height() + Standart.height()/8));
        QWidget::setMinimumSize(min_size);
        QWidget::resize(min_size);
        QSize fix_size(min_size.width(), min_size.height());
        QWidget::setMaximumSize(fix_size);
                 ui->NavcalcProgForm->setIcon(QIcon(":/img/but.png"));
    }

}

//size var
void MainWindow::on_SmallForm_triggered()
{
    ui->calcOut->setFont(QFont("Arial", 10,-1,false));
    ui->calcOutOperator->setFont(QFont("Arial", 10,-1,false));
    ui->calcOutFirst->setFont(QFont("Arial", 10,-1,false));
    size = Esize::small;
    checkSize();
}

void MainWindow::on_MediumForm_triggered()
{
    ui->calcOut->setFont(QFont("Arial", 15,-1,false));
    ui->calcOutOperator->setFont(QFont("Arial", 15,-1,false));
    ui->calcOutFirst->setFont(QFont("Arial", 15,-1,false));
    size = Esize::medium;
    checkSize();
}

void MainWindow::on_LargeForm_triggered()
{
    ui->calcOut->setFont(QFont("Arial", 19,-1,false));
    ui->calcOutOperator->setFont(QFont("Arial", 19,-1,false));
    ui->calcOutFirst->setFont(QFont("Arial", 19,-1,false));
    size = Esize::large;
    checkSize();
}

void MainWindow::setDynamycSizeForm(int a, int b){
    if(a < 220){
     ui->calcOut->setFont(QFont("Arial", 10,-1,false));
     ui->calcOutOperator->setFont(QFont("Arial", 10,-1,false));
     ui->calcOutFirst->setFont(QFont("Arial", 10,-1,false));
    } else if( a < 330) {
        ui->calcOut->setFont(QFont("Arial", 15,-1,false));
        ui->calcOutOperator->setFont(QFont("Arial", 15,-1,false));
        ui->calcOutFirst->setFont(QFont("Arial", 15,-1,false));
    } else{
ui->calcOut->setFont(QFont("Arial", 19,-1,false));
ui->calcOutOperator->setFont(QFont("Arial", 19,-1,false));
ui->calcOutFirst->setFont(QFont("Arial", 19,-1,false));
    }
    sizeDynamycStandart =  QSize(a,b);
    size = Esize::dynamic;
    checkSize();
}

//dynamyc size form
void MainWindow::on_DynamycSizeForm_triggered()
{
    size = Esize::dynamic;
    checkSize();
    ui->DynamycSizeForm->setIcon(QIcon(":/img/but.png"));
    QSize sizeSec = QWidget::size();
    SizeForm *window = new SizeForm(sizeSec);
    window->show();
    connect(window, SIGNAL(getSizeForm(int,int)), this, SLOT(setDynamycSizeForm(int,int))); 


}


//Exit
void MainWindow::on_NavExitCalc_triggered()
{
     QApplication::quit();
}








void MainWindow::on_Maxim_triggered()
{
    QDesktopServices::openUrl(QUrl("https://vk.com/poison_and_style"));

}
