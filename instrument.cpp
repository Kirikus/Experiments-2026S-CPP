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

bool Instrument::from_json(const QJsonObject& obj, Instrument& out, QString& error) {
    // Проверка наличия полей
    if (!obj.contains("id")) {
        error = "Отсутствует поле 'id'";
        return false;
    }
    if (!obj.contains("name")) {
        error = "Отсутствует поле 'name'";
        return false;
    }
    if (!obj.contains("error_value")) {
        error = "Отсутствует поле 'error_value'";
        return false;
    }
    if (!obj.contains("error_type")) {
        error = "Отсутствует поле 'error_type'";
        return false;
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
    if (!obj["error_value"].isDouble()) {
        error = "Поле 'error_value' должно быть числом";
        return false;
    }
    if (!obj["error_type"].isString()) {
        error = "Поле 'error_type' должно быть строкой";
        return false;
    }
    
    // Проверка значений
    QString errorTypeValue = obj["error_type"].toString();
    if (errorTypeValue != "абсолютная" && errorTypeValue != "относительная") {
        error = QString("Недопустимое значение 'error_type': %1. Допустимые значения: абсолютная, относительная.")
                    .arg(errorTypeValue);
        return false;
    }
    
    double errorValue = obj["error_value"].toDouble();
    if (errorValue < 0) {
        error = QString("Недопустимое значение 'error_value': %1. Значение должно быть неотрицательным.")
                    .arg(errorValue);
        return false;
    }
    
    int id = obj["id"].toInt();
    if (id <= 0) {
        error = QString("Недопустимое значение 'id': %1. Значение должно быть натуральным числом.")
                    .arg(id);
        return false;
    }
    
    QString name = obj["name"].toString();
    if (name.isEmpty()) {
        error = "Недопустимое значение 'name'. Значение не может быть пустым.";
        return false;
    }

    // Извлечение значений
    out = Instrument(name, errorValue);
    out.set_id(id);
    out.set_error_type(errorTypeValue);
    return true;
}