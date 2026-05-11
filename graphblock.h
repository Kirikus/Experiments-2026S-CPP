#ifndef GRAPHBLOCK_H
#define GRAPHBLOCK_H

#include <QWidget>
#include "block.h"
class QCustomPlot;

namespace Ui {
class GraphBlock;
}

class GraphBlock : public Block
{
    Q_OBJECT

public:
    explicit GraphBlock(QWidget *parent = nullptr);
    ~GraphBlock();

    void setPlot(QCustomPlot *sourcePlot);

private:
    Ui::GraphBlock *ui;
};

#endif // GRAPHBLOCK_H
