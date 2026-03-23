#ifndef VARIABLE_TABLE_MODEL
#define VARIABLE_TABLE_MODEL

#include "experiment.h"
#include "QModelIndex"
#include "Qt"

class VariableTableModel : public QAbstractTableModel
{
public:
  explicit VariableTableModel(Experiment& exp);

  int rowCount() const;
  int columnCount() const;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  void setHeader(QString& new_header);

private:
  int rows;
  int columns;
  Experiment& experiment;
  QString header;
};

#endif // VARIABLE_TABLE_MODEL