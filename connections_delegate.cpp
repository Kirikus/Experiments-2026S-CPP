#include "connections_delegate.h"
#include <QComboBox>
#include <QModelIndex>
#include <QMouseEvent>

ConnectionsDelegate::ConnectionsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    experiment = Experiment::getInstance();
}

QWidget *ConnectionsDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    if (index.column() == 1) {
        QComboBox *editor = new QComboBox(parent);

        const QHash<int, Instrument>& instruments = experiment->getInstruments();
        for (const Instrument& inst : instruments.values()) {
            editor->addItem(inst.get_name(), inst.get_id());
        }
        editor->addItem("Не выбран", -1);
        return editor;
    }
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

// ДОБАВЛЕНО: открытие редактора только по двойному клику
bool ConnectionsDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        QWidget *editor = createEditor(nullptr, option, index);
        if (editor) {
            setEditorData(editor, index);
            QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
            if (comboBox) {
                comboBox->showPopup();
                // Ждём, пока пользователь выберет значение
                QEventLoop loop;
                connect(comboBox, &QComboBox::currentIndexChanged, &loop, &QEventLoop::quit);
                loop.exec();
            }
            setModelData(editor, model, index);
            delete editor;
        }
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}