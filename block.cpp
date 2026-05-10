#include "block.h"
#include <QPushButton>
#include <QVBoxLayout>

Block::Block(QWidget *parent)
    : QWidget(parent)
{
}

Block::~Block()
{
}


void Block::setupBlockButtons()
{
    QPushButton *upButton = findChild<QPushButton*>("UpButton");
    QPushButton *downButton = findChild<QPushButton*>("DownButton");
    QPushButton *delButton = findChild<QPushButton*>("DelButton");
    
    if (upButton) {
        connect(upButton, &QPushButton::clicked, this, &Block::moveUpButton);
    }
    if (downButton) {
        connect(downButton, &QPushButton::clicked, this, &Block::moveDownButton);
    }
    if (delButton) {
        connect(delButton, &QPushButton::clicked, this, &Block::deleteButton);
    }
}

