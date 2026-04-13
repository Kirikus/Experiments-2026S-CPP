#include "instrument.h"

double Instrument::get_error_value() const {
    return error_value;
}

const QString& Instrument::get_name() const {
    return name;
}