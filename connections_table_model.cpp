#include "connections_table_model.h"

#include "Qt"

ConnectionsTableModel::ConnectionsTableModel(Experiment& exp) : experiment(exp), columns(3) {}

int ConnectionsTableModel::rowCount(const QModelIndex &parent) const {
    // to be implemented
}

int ConnectionsTableModel::columnCount(const QModelIndex &parent) const {
    return columns;
}

QVariant ConnectionsTableModel::data(const QModelIndex &index, int role) const { 
    int row = index.row();
    int col = index.column();

    switch (role) {
        case Qt::DisplayRole:
        
        // to be implemented

            return QVariant();
    }
    return QVariant();
}

bool ConnectionsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;

        switch (index.column()) {
            
            // to be implemented

        }   

        return true;
    }
    return false;
}

QVariant ConnectionsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        // to be implemented
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