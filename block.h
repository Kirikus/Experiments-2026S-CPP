#ifndef BLOCK_H
#define BLOCK_H

#include <QDialog>

namespace Ui {
class Block;
}

class Block : public QDialog
{
    Q_OBJECT

public:
    explicit Block(QWidget *parent = nullptr);
    ~Block();

private:
    Ui::Block *ui;
};

#endif // BLOCK_H
