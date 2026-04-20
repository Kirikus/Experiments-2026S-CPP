#include "instrument_table_model.h"

#include "Qt"

InstrumentTableModel::InstrumentTableModel(Experiment& exp) : experiment(exp), columns(3) {}

int InstrumentTableModel::rowCount(const QModelIndex &parent) const {
    return experiment.getInstruments().size();
}

int InstrumentTableModel::columnCount(const QModelIndex &parent) const {
    return columns;
}

QVariant InstrumentTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        Instrument& instrument = experiment.getInstrument(index.row());

        switch (index.column()) {
            case 0:
                return instrument.get_name();
            case 1:
                return instrument.get_error_value();
            case 2:
                return instrument.get_error_type();
        }
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
            case 0: {
                QString newName = value.toString();
                instrument.set_name(newName);
                break;
            }
            case 1:
                instrument.set_error_value(value.toDouble());
                break;
            case 2: {
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
            return QString("Name");
        case 1:
            return QString("Error value");
        case 2:
            return QString("Error type");
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

void InstrumentTableModel::resetModel() {
    beginResetModel();
    endResetModel();
}