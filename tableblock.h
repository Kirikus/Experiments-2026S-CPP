#ifndef TABLEBLOCK_H
#define TABLEBLOCK_H

#include <QDialog>

namespace Ui {
class TableBlock;
}

class TableBlock : public QDialog
{
    Q_OBJECT

public:
    explicit TableBlock(QWidget *parent = nullptr);
    ~TableBlock();

private:
    Ui::TableBlock *ui;
};

#endif // TABLEBLOCK_H
