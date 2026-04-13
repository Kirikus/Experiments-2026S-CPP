#include "variable_delegate.h"

#include <QPainter>
#include <QComboBox>
#include <QLineEdit>

VariableDelegate::VariableDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void VariableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget *VariableDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    // Для колонки с именем (0) — обычное текстовое поле
    if (index.column() == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    // Для колонки со значениями (1) — пока тоже текстовое поле
    // В будущем можно заменить на что-то более сложное
    else if (index.column() == 1) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void VariableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        lineEdit->setText(value);
    }
}

void VariableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        if (index.column() == 1) {
            // Колонка 1 — значения (QList<double>)
            QString str = lineEdit->text();
            QStringList parts = str.split(',', Qt::SkipEmptyParts);
            QList<double> values;
            for (const QString& part : parts) {
                values.append(part.trimmed().toDouble());
            }
            model->setData(index, QVariant::fromValue(values), Qt::EditRole);
        } else {
            // Все остальные колонки — строки (например, имя)
            model->setData(index, lineEdit->text(), Qt::EditRole);
        }
    }
}

void VariableDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}