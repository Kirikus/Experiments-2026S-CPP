#include "delegate_color.h"
#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    drawBackground(painter, option, index);
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QColorDialog *dialog = new QColorDialog(parent);
    dialog->setOptions(QColorDialog::DontUseNativeDialog);
    return dialog;
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QColorDialog *colorDialog = static_cast<QColorDialog *>(editor);
    model->setData(index, colorDialog->selectedColor(), Qt::EditRole);
}

void ColorDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor color = index.model()->data(index).value<QColor>();
    painter->fillRect(option.rect, color);
}

// открытие редактора ТОЛЬКО по двойному клику
bool ColorDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QWidget *editor = createEditor(nullptr, option, index);
        if (editor)
        {
            QColorDialog *dialog = qobject_cast<QColorDialog *>(editor);
            if (dialog->exec() == QDialog::Accepted)
            {
                setModelData(editor, model, index);
            }
            delete editor;
        }
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}