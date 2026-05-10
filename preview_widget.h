#ifndef PREVIEW_WIDGET_H
#define PREVIEW_WIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QToolButton>
#include "block.h"

class GraphBlock;
class TableBlock;
class TextBlock;

namespace Ui
{
    class Preview_widget;
}

class Preview_widget : public QDialog
{
    Q_OBJECT

public:
    explicit Preview_widget(QWidget *parent = nullptr);
    ~Preview_widget();

private slots:
    void addGraphBlock();
    void addTextBlock();
    void addConstantTable();
    void addVariableTable();
    void addInstrumentTable();
    void SaveReport();
    
private:
    Ui::Preview_widget *ui;
    void setupBlockConnections(Block *block);
    QVBoxLayout *m_blocksLayout;
};

#endif // PREVIEW_WIDGET_H
