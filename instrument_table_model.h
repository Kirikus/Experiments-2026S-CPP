#ifndef INSTRUMENT_TABLE_MODEL_H
#define INSTRUMENT_TABLE_MODEL_H

#include "experiment.h"

class InstrumentTableModel {
public:
  InstrumentTableModel(Experiment& exp);
  int getRowCount();
  int getColumnCount();
  const Instrument& data(int role, int i) const;
  void setData(int i, auto new_data, int data_type); // int data_type: 0 - name, 1 - error_value, 2 - error_type
  QString& getHeader();
  void setHeader(QString& new_header);

private:
  int rowCount;
  int columnCount;
  Experiment& experiment;
  QString header;
};

#endif // INSTRUMENT_TABLE_MODEL