#ifndef CONSTANT_TABLE_MODEL_H
#define CONSTANT_TABLE_MODEL_H

#include "QModelIndex"
#include "Qt"
#include "experiment.h"

class ConstantTableModel : public QAbstractTableModel
{
public:
    explicit ConstantTableModel(Experiment& exp);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setHeader(QString& new_header);

    void addConstant();
    void resetModel();

private:
    int columns;
    Experiment& experiment;
    QString header;
};

#endif // CONSTANT_TABLE_MODEL_H