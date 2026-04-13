#ifndef INSTRUMENT_TABLE_MODEL_H
#define INSTRUMENT_TABLE_MODEL_H

#include "experiment.h"
#include "QModelIndex"
#include "Qt"

class InstrumentTableModel : public QAbstractTableModel
{
public:
  explicit InstrumentTableModel(Experiment& exp);

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

#endif // INSTRUMENT_TABLE_MODEL
