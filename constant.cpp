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

bool Constant::fromJson(const QJsonObject& obj, Constant& out, QString& error) {
    // Проверка наличия полей
    const QStringList required = {"id", "name", "value", "error", "meaning", "readonly"};
    for (const QString& field : required) {
        if (!obj.contains(field)) {
            error = QString("Отсутствует поле '%1'").arg(field);
            return false;
        }
    }

    // Проверка типов
    if (!obj["id"].isDouble()) {
        error = "Поле 'id' должно быть числом";
        return false;
    }
    if (!obj["name"].isString()) {
        error = "Поле 'name' должно быть строкой";
        return false;
    }
    if (!obj["value"].isDouble()) {
        error = "Поле 'value' должно быть числом";
        return false;
    }
    if (!obj["error"].isDouble()) {
        error = "Поле 'error' должно быть числом";
        return false;
    }
    if (!obj["meaning"].isString()) {
        error = "Поле 'meaning' должно быть строкой";
        return false;
    }
    if (!obj["readonly"].isBool()) {
        error = "Поле 'readonly' должно быть true/false";
        return false;
    }

    // Проверка значений
    int id = obj["id"].toInt();
    if (id <= 0) {
        error = QString("Недопустимое значение 'id': %1. Значение должно быть натуральным числом.").arg(id);
        return false;
    }
    QString name = obj["name"].toString();
    if (name.isEmpty()) {
        error = "Недопустимое значение 'name'. Значение не может быть пустым.";
        return false;
    }
    double errorVal = obj["error"].toDouble();
    if (errorVal < 0) {
        error = QString("Недопустимое значение 'error': %1. Значение не может быть отрицательным.").arg(errorVal);
        return false;
    }
    QString meaning = obj["meaning"].toString();
    bool readonly = obj["readonly"].toBool();

    out = Constant(name, obj["value"].toDouble(), errorVal, meaning, readonly);
    out.set_id(id);
    return true;
}