#include "variable.h"

Variable::Variable(QList<double> values, QString name) : values(values), name(name) {}

Variable::Variable() : values(), name() {}

const QList<double>& Variable::get_values() {
    return values;
}

const QString& Variable::get_name() {
    return name;
}