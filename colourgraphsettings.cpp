#include "colourgraphsettings.h"
#include "ui_colourgraphsettings.h"

ColourGraphSettings::ColourGraphSettings(QWidget *parent)
    : GraphSettings(parent)
    , ui(new Ui::ColourGraphSettings)
{
    ui->setupUi(this);
}  

ColourGraphSettings::~ColourGraphSettings()
{
    delete ui;
}

void ColourGraphSettings::applySettings()
{
    
}