#include "variable_table_model.h"

#include "Qt"

VariableTableModel::VariableTableModel(Experiment& exp) : experiment(exp) {}

int VariableTableModel::rowCount() const {
    return rows;
}

int VariableTableModel::rowCount(const QModelIndex &parent) const {
    return experiment.getVariables().size();
}

int VariableTableModel::columnCount(const QModelIndex &parent) const {
    int max = 0;
    for (int i = 0; i < experiment.getVariables().size(); i++) {
        if (experiment.getVariables()[i].get_values().size() > max) {
            max = experiment.getVariables()[i].get_values().size();
        }
    }
    return max + 2;
}

QVariant VariableTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole) {
        Variable& variable = experiment.getVariables()[index.row()];
        switch (index.column()) {
            case 0:
                return variable.get_name();
            default:
                QList<double> values = variable.get_values();
                if (col >= 1 && col - 1 < values.size()) {
                    return values[col - 1];
                } else {
                    return QVariant(); // или 0.0, или другое значение по умолчанию
                }
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

        int currentSize = variable.get_values().size();

        switch (index.column()) {
            case 0: {
                QString newName = value.toString();
                variable.set_name(newName);
                break;
            }
            default:
            if (index.column() - 1 < variable.get_values().size()) {
                variable.get_values()[index.column() - 1] = value.toDouble();
            } else if (index.column() - 1 == variable.get_values().size()) {
                int oldMax = 0;
                for (int i = 0; i < experiment.getVariables().size(); i++) {
                    if (experiment.getVariables()[i].get_values().size() > oldMax) {
                        oldMax = experiment.getVariables()[i].get_values().size();
                    }
                }
                variable.get_values().append(value.toDouble());
                int newMax = 0;
                for (int i = 0; i < experiment.getVariables().size(); i++) {
                    if (experiment.getVariables()[i].get_values().size() > newMax) {
                        newMax = experiment.getVariables()[i].get_values().size();
                    }
                }
                if (newMax > oldMax) {
                    beginInsertColumns(QModelIndex(), newMax, newMax);
                    endInsertColumns();
                }
            }
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
            return QString("Name");
        default:
            return QString("Value ") + QString::number(section);
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
