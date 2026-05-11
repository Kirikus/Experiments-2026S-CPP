#include "variable.h"
#include "instrument.h"

Variable::Variable(QList<double> values, QString name) : values(values), name(name), instrument_id(-1) {}

Variable::Variable() : values(), name(), id(), instrument_id(-1) {}

QList<double>& Variable::get_values() {
    return values;
}

// ДОБАВЛЕНО: константная версия
const QList<double>& Variable::get_values() const {
    return values;
}

void Variable::set_values(QList<double>& new_values) {
    values = new_values;
}

void Variable::add_value(double new_value) {
    values.append(new_value);
}

void Variable::set_name(const QString& new_name) {
    name = new_name;
}

const QString& Variable::get_name() const {
    return name;
}

int Variable::get_id() const {
    return id;
}

void Variable::set_id(int new_id) {
    id = new_id;
}

int Variable::get_instrument_id() const {
    return instrument_id;
}

void Variable::set_instrument_id(int new_id) {
    instrument_id = new_id;
}

QJsonObject Variable::to_json() const {
    QJsonObject variable;
    QJsonArray values_list;
    variable["id"] = id;
    variable["instrument_id"] = instrument_id;
    variable["name"] = name;
    for (int j = 0; j < values.size(); j++) {
        values_list.append(values[j]);
    }
    variable["values"] = values_list;
    return variable;
}

bool Variable::fromJson(const QJsonObject& obj, const QHash<int, Instrument>& instruments,
                        Variable& out, QString& error) {
    const QStringList required = {"id", "name", "instrument_id", "values"};
    for (const QString& field : required) {
        if (!obj.contains(field)) {
            error = QString("Отсутствует поле '%1'").arg(field);
            return false;
        }
    }
    if (!obj["id"].isDouble()) {
        error = "Поле 'id' должно быть числом";
        return false;
    }
    if (!obj["name"].isString()) {
        error = "Поле 'name' должно быть строкой";
        return false;
    }
    if (!obj["instrument_id"].isDouble()) {
        error = "Поле 'instrument_id' должно быть числом";
        return false;
    }
    if (!obj["values"].isArray()) {
        error = "Поле 'values' должно быть массивом";
        return false;
    }
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
    int instrumentId = obj["instrument_id"].toInt();
    if (instrumentId != -1) {
        if (instrumentId <= 0) {
            error = QString("Недопустимое значение 'instrument_id': %1. Допустимы -1 или положительное число.").arg(instrumentId);
            return false;
        }
        if (!instruments.contains(instrumentId)) {
            error = QString("Недопустимое значение 'instrument_id': %1. Инструмент с таким id не найден.").arg(instrumentId);
            return false;
        }
    }
    QJsonArray valuesArray = obj["values"].toArray();
    QList<double> values;
    for (const QJsonValue& v : valuesArray) {
        if (!v.isDouble()) {
            error = "Недопустимое значение в массиве 'values': элемент не является числом.";
            return false;
        }
        values.append(v.toDouble());
    }
    out = Variable(values, name);
    out.set_id(id);
    out.set_instrument_id(instrumentId);
    return true;
}