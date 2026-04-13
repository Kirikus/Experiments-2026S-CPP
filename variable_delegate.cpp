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
        editor->setFrame(false); // Отключаем рамку, чтобы не было визуальных артефактов
        return editor;
    }
    // Для колонки со значениями (1 и далее) — текстовое поле
    else if (index.column() >= 1) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false); // Отключаем рамку
        QDoubleValidator *validator = new QDoubleValidator(editor);
        validator->setRange(-99999.99, 99999.99);
        validator->setDecimals(3);
        validator->setLocale(QLocale::C);
        validator->setNotation(QDoubleValidator::StandardNotation);
        editor->setValidator(validator);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void VariableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        lineEdit->setText(value);
    }
}

void VariableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        if (index.column() == 0) {
            // Имя переменной
            model->setData(index, lineEdit->text(), Qt::EditRole);
        } else {
            // Значение переменной
            bool ok;
            double value = lineEdit->text().toDouble(&ok);
            if (ok) {
                model->setData(index, value, Qt::EditRole);
            }
        }
    }
}

void VariableDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}