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
        error = "Отсутствует поле 'id' для Instrument";
        return false;
    }
    if (!obj.contains("name")) {
        error = "Отсутствует поле 'name' для Instrument";
        return false;
    }
    if (!obj.contains("error_value")) {
        error = "Отсутствует поле 'error_value' для Instrument";
        return false;
    }
    if (!obj.contains("error_type")) {
        error = "Отсутствует поле 'error_type' для Instrument";
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
    if (obj["error_type"].toString() != "абсолютная" && obj["error_type"].toString() != "относительная") {
        error = "Недопустимое значение 'error_type': " + obj["error_type"].toString();
        return false;
    }
    if (obj["error_value"].toDouble() < 0) {
        error = "Недопустимое значение 'error_value': " + obj["error_value"].toString() + 
            ". Значение должно быть неотрицательно.";
        return false;
    }
    if (obj["id"].toInt() < 0) {
        error = "Недопустимое значние id: " + obj["id"].toString() + 
            ". id должен быть натуральным числом.";
        return false;
    }
    if (obj["name"].toString().isEmpty()) {
        error = "Значение 'name' не может быть пустым";
        return false;
    }
    if (obj["error_type"].toString().isEmpty()) {
        error = "Значение 'error_type' не может быть пустым";
        return false;
    }

    // Извлечение значений
    int id = obj["id"].toInt();
    QString name = obj["name"].toString();
    double errorValue = obj["error_value"].toDouble();
    QString errorType = obj["error_type"].toString();

    out = Instrument(name, errorValue);
    out.set_id(id);
    out.set_error_type(errorType);
    return true;
}