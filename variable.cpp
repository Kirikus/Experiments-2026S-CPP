#include "variable.h"
#include "instrument.h"

Variable::Variable(QList<double> values, QString name, const Instrument* inst) : values(values), name(name), instrument(inst), instrument_id(inst->get_id()) {}

Variable::Variable() : values(), name() , instrument() , id() , instrument_id() {}

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

const Instrument* Variable::get_instrument() const {
    return instrument;
} 

void Variable::set_instrument(const Instrument* inst) {
    instrument = inst;
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