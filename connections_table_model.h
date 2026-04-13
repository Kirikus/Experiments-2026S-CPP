#ifndef CONNECTIONS_TABLE_MODEL_H
#define CONNECTIONS_TABLE_MODEL_H

#include "experiment.h"
#include "QModelIndex"
#include "Qt"

class ConnectionsTableModel : public QAbstractTableModel
{
public:
  explicit ConnectionsTableModel(Experiment& exp);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  void setHeader(QString& new_header);
  void resetModel();

private:
  int columns;
  Experiment& experiment;
  QString header;
};

#endif // CONNECTIONS_TABLE_MODEL_H