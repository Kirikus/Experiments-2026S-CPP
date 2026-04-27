#include "constant_table_model.h"
#include "Qt"


ConstantTableModel::ConstantTableModel(Experiment& exp) : columns(4), experiment(exp)
{
}

int ConstantTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return experiment.getConstants().size();
}

int ConstantTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns;
}

QVariant ConstantTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {

        const Constant& constant = experiment.getConstants()[index.row()];

        switch (index.column())
        {
        case 0:
            return constant.get_name();
        case 1:
            return constant.get_value();
        case 2:
            return constant.get_error();
        case 3:
            return constant.get_meaning();
        }
    }
    return QVariant();
}

bool ConstantTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;

        Constant& constant = experiment.getConstants()[index.row()];

        switch (index.column())
        {
        case 0:
            constant.set_name(value.toString());
            break;
        case 1:
            constant.set_value(value.toDouble());
            break;
        case 2:
            constant.set_error(value.toDouble());
            break;
        case 3:
            constant.set_meaning(value.toString());
            break;
        default:
            return false;
        }

        return true;
    }
    return false;
}

QVariant ConstantTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("Имя");
        case 1:
            return QString("Значение");
        case 2:
            return QString("Погрешность");
        case 3:
            return QString("Обозначение");
        }
    }
    return QVariant();
}

void ConstantTableModel::setHeader(QString &new_header)
{
    header = new_header;
}

Qt::ItemFlags ConstantTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    const Constant& constant = experiment.getConstants()[index.row()];

    if (!constant.get_readonly()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void ConstantTableModel::resetModel() {
    beginResetModel();
    endResetModel();
}