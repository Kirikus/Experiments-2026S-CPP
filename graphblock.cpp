#include "graphblock.h"
#include "ui_graphblock.h"
#include <qcustomplot.h>

GraphBlock::GraphBlock(QWidget *parent)
    : Block(parent)
    , ui(new Ui::GraphBlock)
{
    ui->setupUi(this);

    connect(ui->upButton, &QPushButton::clicked, this, &Block::moveUpButton);
    connect(ui->downButton, &QPushButton::clicked, this, &Block::moveDownButton);
    connect(ui->deleteButton, &QPushButton::clicked, this, &Block::deleteButton);
}

GraphBlock::~GraphBlock()
{
    delete ui;
}

//отрисовка картинки графика
void GraphBlock::setPlot(QCustomPlot *sourcePlot)
{
    if (sourcePlot) {
        QPixmap pixmap = sourcePlot->toPixmap();
        ui->imageLabel->setPixmap(pixmap.scaled(400, 300, Qt::KeepAspectRatio));
    }
}

