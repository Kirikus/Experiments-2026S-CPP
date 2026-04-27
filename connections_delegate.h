#ifndef CONNECTIONS_DELEGATE_H
#define CONNECTIONS_DELEGATE_H

#include <QStyledItemDelegate>
#include "experiment.h"

class ConnectionsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ConnectionsDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const override;

private:
    mutable Experiment* experiment = nullptr;
};

#endif // CONNECTIONS_DELEGATE_H