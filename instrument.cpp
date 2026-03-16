#include "instrument.h"

Instrument::Instrument(const QString& name, double error_value) : name(name), error_value(error_value) {}

double Instrument::get_error_value() const {
    return error_value;
}

const QString& Instrument::get_name() const {
    return name;
}

const QString& Instrument::get_error_type() const {
    return error_type;
}