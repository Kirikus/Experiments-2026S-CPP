#include "connections_table_model.h"

#include "Qt"

#include <iostream>

ConnectionsTableModel::ConnectionsTableModel(Experiment& exp) : experiment(exp), columns(3) {}

int ConnectionsTableModel::rowCount(const QModelIndex &parent) const {
    return experiment.getVariables().size();
}

int ConnectionsTableModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant ConnectionsTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    switch (role) {
        case Qt::DisplayRole:
            switch (index.column()) {
                case 0:
                    return experiment.getVariables()[index.row()].get_name();
                case 1: 
                    if (experiment.getVariables()[index.row()].get_instrument() == nullptr) {
                        return QVariant();
                    }
                    return experiment.getVariables()[index.row()].get_instrument()->get_name();
                }
        }
    return QVariant();
}

bool ConnectionsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !checkIndex(index))
      return false;
    
    if (index.column() == 1) {
            QString instrument_name = value.toString();
            for (auto& instrument : experiment.getInstruments()) {
                if (instrument.get_name() == instrument_name) {
                    experiment.getVariables()[index.row()].set_instrument(&instrument);
                    return true;
                }
            }
    }
    return true;
}

QVariant ConnectionsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QString("Variable");
            case 1:
                return QString("Instrument");
        }
    }
    return QVariant();
}

void ConnectionsTableModel::setHeader(QString& new_header) {
    header = new_header;
}

Qt::ItemFlags ConnectionsTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void ConnectionsTableModel::resetModel() {
    beginResetModel();
    endResetModel();
}