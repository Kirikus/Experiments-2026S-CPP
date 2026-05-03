#include "variable.h"
#include "instrument.h"

Variable::Variable(QList<double> values, QString name) : values(values), name(name), instrument_id(-1) {}

Variable::Variable() : values(), name() , id() , instrument_id(-1) {}

QList<double>& Variable::get_values() {
    return values;
}

void Variable::set_values(QList<double>& new_values) {
    values = new_values;
}

void Variable::add_value(double new_value){
    values.append(new_value);
}

void Variable::set_name(const QString& new_name){
    name = new_name;
}

const QString& Variable::get_name() {
    return name;
}

int Variable::get_id() const {
    return id;
}

void Variable::set_id(int new_id) {
    id = new_id;
}

int Variable::get_instrument_id() const {
    return instrument_id;
}

void Variable::set_instrument_id(int new_id) {
    instrument_id = new_id;
}