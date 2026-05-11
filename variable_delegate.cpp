#include "variable_delegate.h"
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QMouseEvent>

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
    if (index.column() == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
        return editor;
    }
    else if (index.column() >= 1) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setFrame(false);
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
            model->setData(index, lineEdit->text(), Qt::EditRole);
        } else {
            bool ok;
            double value = lineEdit->text().toDouble(&ok);
            if (ok) {
                model->setData(index, value, Qt::EditRole);
            }
        }
    }
}

// открытие редактора только по двойному клику
bool VariableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        QWidget *editor = createEditor(nullptr, option, index);
        if (editor) {
            setEditorData(editor, index);
            QWidget editorWidget;
            editor->setParent(&editorWidget);
            QStyledItemDelegate::setModelData(editor, model, index);
            model->setData(index, editor->property("text").isValid() ? editor->property("text") : QVariant(), Qt::EditRole);
            delete editor;
        }
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}