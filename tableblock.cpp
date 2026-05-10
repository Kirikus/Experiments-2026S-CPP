#include "tableblock.h"
#include "ui_tableblock.h"

TableBlock::TableBlock(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TableBlock)
{
    ui->setupUi(this);
}

TableBlock::~TableBlock()
{
    delete ui;
}
