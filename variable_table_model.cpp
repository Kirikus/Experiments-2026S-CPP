#include "variable_table_model.h"

#include "Qt"

VariableTableModel::VariableTableModel(Experiment& exp) : experiment(exp) {}

int VariableTableModel::rowCount() const {
    return rows;
}

int VariableTableModel::columnCount() const {
    return columns;
}

QVariant VariableTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
            case 0:
                return variable.get_name();
            case 1:
                // Формируем строку со значениями, разделенными запятыми
                QString valuesStr;
                const QList<double>& values = variable.get_values();
                for (int i = 0; i < values.size(); ++i) {
                    if (i > 0) valuesStr += ", ";
                    valuesStr += QString::number(values[i]);
                }
                return valuesStr;
        }
    }
    return QVariant();
}

bool VariableTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        Variable& variable = experiment.getVariables()[index.row()];

        switch (index.column()) {
            case 0: {
                QString newName = value.toString();
                variable.set_name(newName);
                break;
            }
            case 1:
                // Значение передается как QList<double>
                QList<double> newValues = value.value<QList<double>>();
                variable.set_values(newValues);
                break;
        }   

        return true;
    }
    return false;
}

QVariant VariableTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Имя");
        case 1:
            return QString("Значения");
        }
    }
    return QVariant();
}

void VariableTableModel::setHeader(QString& new_header) {
    header = new_header;
}

Qt::ItemFlags VariableTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
