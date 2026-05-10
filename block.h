#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>

class Block : public QWidget
{
    Q_OBJECT

public:
    explicit Block(QWidget *parent = nullptr);
    virtual ~Block();

signals:
    void moveUpButton();
    void moveDownButton();
    void deleteButton();

    protected:
    void setupBlockButtons();
};

#endif // BLOCK_H