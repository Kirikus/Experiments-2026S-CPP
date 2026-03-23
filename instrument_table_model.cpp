#include "instrument_table_model.h"

#include "Qt"

InstrumentTableModel::InstrumentTableModel(Experiment& exp) : experiment(exp) {}

int InstrumentTableModel::rowCount() const {
    return rows;
}

int InstrumentTableModel::columnCount() const {
    return columns;
}

QVariant InstrumentTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        if (row == 0 && col == 1) return QString("<--left");
        if (row == 1 && col == 1) return QString("right-->");

        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col + 1);
    }
    return QVariant();
}

bool InstrumentTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        Instrument& instrument = experiment.getInstrument(index.row());

        switch (index.column()) {
            case 1: {
                QString newName = value.toString();
                instrument.set_name(newName);
                break;
            }
            case 2:
                instrument.set_error_value(value.toDouble());
                break;
            case 3: {
                QString newErrorType = value.toString();
                instrument.set_error_type(newErrorType);
                break;
            }
        }   

        return true;
    }
    return false;
}

QVariant InstrumentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("first");
        case 1:
            return QString("second");
        case 2:
            return QString("third");
        }
    }
    return QVariant();
}

void InstrumentTableModel::setHeader(QString& new_header) {
    header = new_header;
}

Qt::ItemFlags InstrumentTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
