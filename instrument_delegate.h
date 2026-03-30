#ifndef INSTRUMENT_DELEGATE_H
#define INSTRUMENT_DELEGATE_H

#include <QStyledItemDelegate>

class InstrumentDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit InstrumentDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const override;
};

#endif // INSTRUMENT_DELEGATE_H