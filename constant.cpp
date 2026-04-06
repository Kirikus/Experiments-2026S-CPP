#include "constant.h"

Constant::Constant(const QString& name, double value, double error, const QString& meaning, bool readonly) :
name(name), value(value), error(error), meaning(meaning), readonly(readonly) {

}

double Constant::get_value() const {
    return value;
}
double Constant::get_error() const {
    return error;
}
QString Constant::get_meaning() const {
    return meaning;
}
QString Constant::get_name() const {
    return name;
}

void Constant::set_value(double new_value) {
    if (!readonly) {
        value = new_value;
    }
}

void Constant::set_error(double new_error) {
    if (!readonly) {
        error = new_error;
    }
}

void Constant::set_meaning(const QString &new_meaning) {
    if (!readonly) {
        meaning = new_meaning;
    }
}

void Constant::set_name(const QString &new_name) {
    if (!readonly) {
    name = new_name;
    }
}