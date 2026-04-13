#include "variable.h"

Variable::Variable(QList<double> values, QString name) : values(values), name(name) {}

Variable::Variable() : values(), name() {}

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