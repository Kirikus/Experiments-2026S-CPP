#include "preview_widget.h"
#include "ui_preview_widget.h"

Preview_widget::Preview_widget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Preview_widget)
{
    ui->setupUi(this);
}

Preview_widget::~Preview_widget()
{
    delete ui;
}
