#include "lingraphsettings.h"
#include "ui_lingraphsettings.h"

LinGraphSettings::LinGraphSettings(QWidget *parent)
    : GraphSettings(parent)
    , ui(new Ui::LinGraphSettings)
{
    ui->setupUi(this);
}

LinGraphSettings::~LinGraphSettings()
{
    delete ui;
}

void LinGraphSettings::applySettings()
{
    
}
