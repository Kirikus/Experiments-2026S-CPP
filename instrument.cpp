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

void Instrument::set_error_value(double new_error_value) {
    error_value = new_error_value;
}
void Instrument::set_name(QString& new_name) {
    name = new_name;
}
void Instrument::set_error_type(QString& new_error_type) {
    error_type = new_error_type;
}

int Instrument::get_id() const {
    return id;
}

void Instrument::set_id(int new_id) {
    id = new_id;
}

QJsonObject Instrument::to_json() const {
    QJsonObject instrument;
    instrument["id"] = id;
    instrument["error_type"] = error_type;
    instrument["name"] = name;
    instrument["error_value"] = error_value;
    return instrument;
}