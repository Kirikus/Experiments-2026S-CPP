#include "tableblock.h"
#include "ui_tableblock.h"
#include <QAbstractItemModel>

TableBlock::TableBlock(QWidget *parent)
    : Block(parent)
    , ui(new Ui::TableBlock)
{
    ui->setupUi(this);

    connect(ui->upButton, &QPushButton::clicked, this, &Block::moveUpButton);
    connect(ui->downButton, &QPushButton::clicked, this, &Block::moveDownButton);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Block::deleteButton);
}

TableBlock::~TableBlock()
{
    delete ui;
}

//отображение таблицы
void TableBlock::setModel(QAbstractItemModel *model)
{
    ui->tableView->setModel(model);
}
