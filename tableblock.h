#ifndef TABLEBLOCK_H
#define TABLEBLOCK_H

#include <QWidget>
#include "block.h"


class QAbstractItemModel;

namespace Ui {
class TableBlock;
}

class TableBlock : public Block
{
    Q_OBJECT

public:
    explicit TableBlock(QWidget *parent = nullptr);
    ~TableBlock();

    void setModel(QAbstractItemModel *model);

private:
    Ui::TableBlock *ui;
};

#endif // TABLEBLOCK_H
