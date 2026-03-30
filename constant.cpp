#include "constant.h"

Constant::Constant(QString& name, double& value, QString& meaning, bool readonly) :
name(name), value(value), meaning(meaning), readonly(readonly) {

}

double Constant::get_value() {
    return value;
}
QString Constant::get_meaning() {
    return meaning;
}
QString Constant::get_name() {
    return name;
}

void Constant::set_value(double& new_value) {
    if (!readonly) {
        value = new_value;
    }
}

void Constant::set_meaning(double& new_meaning) {
    if (!readonly) {
        meaning = new_meaning;
    }
}

void Constant::set_name(QString& new_name) {
    if (!readonly) {
    name = new_name;
    }
}