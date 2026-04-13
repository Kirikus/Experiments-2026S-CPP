#include "constant.h"

Constant::Constant(double& value, double& error, QString& name, bool readonly) :
value(value), error(error), name(name), readonly(readonly) {

}

double Constant::get_value() const {
    return value;
}
double Constant::get_error() const {
    return error;
}
QString Constant::get_name() const {
    return name;
}