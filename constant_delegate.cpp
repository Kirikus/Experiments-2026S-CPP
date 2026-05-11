#include "constant_delegate.h"
#include <QPainter>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QMouseEvent>

ConstantDelegate::ConstantDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ConstantDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget *ConstantDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    int column = index.column();

    if (column == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    else if (column == 1) {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(-999999.0);
        editor->setMaximum(999999.0);
        editor->setDecimals(6);
        editor->setSingleStep(0.1);
        return editor;
    }
    else if (column == 2) {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(-999999.0);
        editor->setMaximum(999999.0);
        editor->setDecimals(6);
        editor->setSingleStep(0.1);
        return editor;
    }
    else if (column == 3) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ConstantDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant data = index.model()->data(index, Qt::DisplayRole);

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);

    if (lineEdit) {
        lineEdit->setText(data.toString());
    } else if (spinBox) {
        spinBox->setValue(data.toDouble());
    }
}

void ConstantDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);

    if (lineEdit) {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    } else if (spinBox) {
        model->setData(index, spinBox->value(), Qt::EditRole);
    }
}

void ConstantDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

// ДОБАВЛЕНО: открытие редактора только по двойному клику
bool ConstantDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        QWidget *editor = createEditor(nullptr, option, index);
        if (editor) {
            setEditorData(editor, index);
            setModelData(editor, model, index);
            delete editor;
        }
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}