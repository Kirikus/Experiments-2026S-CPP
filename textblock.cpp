#include "textblock.h"
#include "ui_textblock.h"

TextBlock::TextBlock(QWidget *parent)
    : Block(parent)
    , ui(new Ui::TextBlock)
{
    ui->setupUi(this);
    setupBlockButtons();
}

TextBlock::~TextBlock()
{
    delete ui;
}
