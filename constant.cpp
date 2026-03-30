#include "constant.h"

Constant::Constant(const QString& name, double value, const QString& meaning, bool readonly) :
name(name), value(value), meaning(meaning), readonly(readonly) {

}

double Constant::get_value() const {
    return value;
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