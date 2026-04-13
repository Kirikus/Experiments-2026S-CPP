#include "constant.h"

Constant::Constant(double& value, double& error, QString& name, bool readonly) :
value(value), error(error), name(name), readonly(readonly) {

}

double Constant::get_value() {
    return value;
}
double Constant::get_error() {
    return error;
}
QString Constant::get_name() {
    return name;
}

void Constant::set_value(double& new_value) {
    if (!readonly) {
        value = new_value;
    }
}

void Constant::set_error(double& new_error) {
    if (!readonly) {
        error = new_error;
    }
}

void Constant::set_name(QString& new_name) {
    name = new_name;
}