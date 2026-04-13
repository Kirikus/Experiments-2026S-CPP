#ifndef DELEGATE_COLOR_H
#define DELEGATE_COLOR_H

#include <QStyledItemDelegate>

class ColorDelegate: public QStyledItemDelegate
{
public:
    ColorDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {}

public:
    virtual void paint(QPainter *painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;
    QWidget * createEditor(QWidget * parent,
                           const QStyleOptionViewItem &,
                           const QModelIndex & index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
protected:
    virtual void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // DELEGATE_COLOR_H
