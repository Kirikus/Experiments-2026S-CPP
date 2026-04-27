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

        const QList<Instrument>& instruments = experiment->getInstruments();
        for (const Instrument& inst : instruments) {
            editor->addItem(inst.get_name());
        }

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

    QString currentName = index.model()->data(index, Qt::DisplayRole).toString();
    comboBox->setCurrentText(currentName);
}

void ConnectionsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    if (index.column() != 1) return;

    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) return;

    QString selectedName = comboBox->currentText();
    model->setData(index, selectedName, Qt::EditRole);
}
