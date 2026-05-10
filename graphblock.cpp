#include "graphblock.h"
#include "ui_graphblock.h"

GraphBlock::GraphBlock(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GraphBlock)
{
    ui->setupUi(this);
}

GraphBlock::~GraphBlock()
{
    delete ui;
}
