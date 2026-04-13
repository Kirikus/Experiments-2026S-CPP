#include "instrument_delegate.h"

#include <QPainter>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>

InstrumentDelegate::InstrumentDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void InstrumentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget *InstrumentDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    // Колонка 0 — имя (текст)
    if (index.column() == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    // Колонка 1 — ошибка (число)
    else if (index.column() == 1) {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(0.0);
        editor->setMaximum(999999.0);
        editor->setDecimals(6);
        return editor;
    }
    // Колонка 2 — тип ошибки (выбор из списка)
    else if (index.column() == 2) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems({"Абсолютная", "Относительная"});
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void InstrumentDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);

    if (lineEdit) {
        lineEdit->setText(value);
    } else if (spinBox) {
        spinBox->setValue(value.toDouble());
    } else if (comboBox) {
        comboBox->setCurrentText(value);
    }
}

void InstrumentDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);

    if (lineEdit) {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    } else if (spinBox) {
        model->setData(index, spinBox->value(), Qt::EditRole);
    } else if (comboBox) {
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
}

void InstrumentDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}