#ifndef GRAPHBLOCK_H
#define GRAPHBLOCK_H

#include <QDialog>

namespace Ui {
class GraphBlock;
}

class GraphBlock : public QDialog
{
    Q_OBJECT

public:
    explicit GraphBlock(QWidget *parent = nullptr);
    ~GraphBlock();

private:
    Ui::GraphBlock *ui;
};

#endif // GRAPHBLOCK_H
