#ifndef VARIABLE_DELEGATE_H
#define VARIABLE_DELEGATE_H

#include <QStyledItemDelegate>

class VariableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit VariableDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

};

#endif // VARIABLE_DELEGATE_H