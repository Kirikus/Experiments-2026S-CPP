#include "bargraphsettings.h"
#include "ui_bargraphsettings.h"

BarGraphSettings::BarGraphSettings(QWidget *parent)
    : GraphSettings(parent)
    , ui(new Ui::BarGraphSettings)
{
    ui->setupUi(this);
}

BarGraphSettings::~BarGraphSettings()
{
    delete ui;
}

void BarGraphSettings::applySettings()
{
    
}
