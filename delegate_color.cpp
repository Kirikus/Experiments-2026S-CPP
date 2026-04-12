#include "delegate_color.h"

#include <QColorDialog>
#include <QColor>
#include <QPainter>

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    drawBackground(painter, option, index);
    QStyledItemDelegate::paint(painter, option, index);
}
QWidget * ColorDelegate::createEditor(QWidget * parent,
                                      const QStyleOptionViewItem &, const QModelIndex & index) const
{
    auto dialog = new QColorDialog(parent);
    return dialog;
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QColorDialog *color_dialog = static_cast<QColorDialog*>(editor);
    model->setData(index, color_dialog->selectedColor(), Qt::EditRole);
}
void ColorDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->fillRect(option.rect, index.model()->data(index).value<QColor>());
}
