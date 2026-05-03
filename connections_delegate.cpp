#include "connections_delegate.h"

#include <QComboBox>
#include <QModelIndex>

ConnectionsDelegate::ConnectionsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    experiment = Experiment::getInstance();
}

QWidget *ConnectionsDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    // Редактируем только столбец 1 (инструменты)
    if (index.column() == 1) {
        QComboBox *editor = new QComboBox(parent);

        const QHash<int, Instrument>& instruments = experiment->getInstruments();
        for (const Instrument& inst : instruments.values()) {
            editor->addItem(inst.get_name(), inst.get_id());
        }

        editor->addItem("Не выбран", -1);

        return editor;
    }

    // Для других столбцов не создаём редактор
    return nullptr;
}

void ConnectionsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() != 1) return;

    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) return;

    int currentId = index.model()->data(index, Qt::EditRole).toInt();
    int idx = comboBox->findData(currentId, Qt::UserRole);
    if (idx >= 0)
        comboBox->setCurrentIndex(idx);
}

void ConnectionsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    if (index.column() != 1) return;

    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) return;

    QVariant selected_id = comboBox->currentData(Qt::UserRole);
    model->setData(index, selected_id, Qt::EditRole);
}
