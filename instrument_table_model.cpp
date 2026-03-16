#include "instrument_table_model.h"

#include "Qt"

InstrumentTableModel::InstrumentTableModel(Experiment& exp) : experiment(exp) {}

int InstrumentTableModel::getRowCount() {
    return rowCount;
}

int InstrumentTableModel::getColumnCount() {
    return columnCount;
}

const Instrument& InstrumentTableModel::data(int role, int i) const { 
    if (role == Qt::DisplayRole) {
        return experiment.getInstrument(i);
    }
}

void InstrumentTableModel::setData(int i, auto new_data, int data_type) {
    Instrument& instrument = experiment.getInstrument(i);
    if (data_type == 0) {
        instrument.set_name(new_data);
    } else if (data_type == 1) {
        instrument.set_error_value(new_data);
    } else if (data_type == 2) {
        instrument.set_error_type(new_data);
    } else {
        throw std::invalid_argument("data_type must be 0 to 2");
    }
}

QString& InstrumentTableModel::getHeader() {
    return header;
}
void InstrumentTableModel::setHeader(QString& new_header) {
    header = new_header;
}
