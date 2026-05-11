#include "colourgraphsettings.h"
#include "ui_colourgraphsettings.h"
#include <QDialogButtonBox>
#include <QPushButton>

ColourGraphSettings::ColourGraphSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::ColourGraphSettings)
{
    ui->setupUi(this);

    connect(ui->SaveButton, &QPushButton::clicked, this, &ColourGraphSettings::onSave);
    connect(ui->CancelButton, &QPushButton::clicked, this, &ColourGraphSettings::onCancel);
}

ColourGraphSettings::~ColourGraphSettings()
{
    delete ui;
}

void ColourGraphSettings::onSave()
{
    emit settingsApplied();
    accept();
}

void ColourGraphSettings::onCancel()
{
    reject();
}