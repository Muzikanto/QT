#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
   connect(ui->settingsButton, SIGNAL(clicked()), this, SIGNAL(setSizeMainFormSignal()));
}

Settings::~Settings()
{
    delete ui;
}

QString Settings::sizeData()
{
    return ui->widthCalcMainFormInput->text();
}



