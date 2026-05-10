#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <QWidget>
#include "block.h"

namespace Ui {
class TextBlock;
}

class TextBlock : public Block
{
    Q_OBJECT

public:
    explicit TextBlock(QWidget *parent = nullptr);
    ~TextBlock();

private:
    Ui::TextBlock *ui;
};

#endif // TEXTBLOCK_H
