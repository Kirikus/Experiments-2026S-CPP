#include "constant.h"

Constant::Constant(const QString& name, double value, double error, const QString& meaning, bool readonly) :
    name(name), value(value), error(error), meaning(meaning), readonly(readonly) {
}

QString Constant::get_name() const {
    return name;
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

void Constant::set_name(const QString& name) {
    this->name = name;
}

void Constant::set_value(double value) {
    if (!readonly) {
        this->value = value;
    }
}

void Constant::set_error(double error) {
    if (!readonly) {
        this->error = error;
    }
}

void Constant::set_meaning(const QString& meaning) {
    if (!readonly) {
        this->meaning = meaning;
    }
}

bool Constant::get_readonly() const {
    return readonly;
}

int Constant::get_id() const {
    return id;
}

void Constant::set_id(int new_id) {
    id = new_id;
}

QJsonObject Constant::to_json() const {
    QJsonObject constant;
    constant["id"] = id;
    constant["name"] = name;
    constant["value"] = value;
    constant["meaning"] = meaning;
    constant["readonly"] = readonly;
    return constant;
}