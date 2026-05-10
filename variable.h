#ifndef VARIABLE_H
#define VARIABLE_H

#include <QList>
#include <QString>
#include "instrument.h"
#include <QJsonObject>
#include <QJsonArray>

class Variable{
public:
  Variable(QList<double> values, QString name);
  Variable();

  QList<double>& get_values();
  const QString& get_name();

  void set_values(QList<double>& new_values);
  void add_value(double new_value);
  void set_name(const QString& new_name);
  int get_id() const;
  void set_id(int id);
  int get_instrument_id() const;
  void set_instrument_id(int id);
  QJsonObject to_json() const;
  
private:
  int id;
  QList<double> values;
  QString name;
  int instrument_id;
};

#endif // VARIABLE_H