#ifndef CONSTANT_TABLE_MODEL_H
#define CONSTANT_TABLE_MODEL_H


#include "QModelIndex"
#include "Qt"
#include "constant.h"

class ConstantTableModel : public QAbstractTableModel
{
public:
    explicit ConstantTableModel();

    int rowCount() const;
    int columnCount() const;
    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setHeader(QString& new_header);

    void addConstant(); // добавление строки

private:
    int rows;
    int columns;
    QList<Constant> constants;
    QString header;
};

#endif // CONSTANT_TABLE_MODEL_H