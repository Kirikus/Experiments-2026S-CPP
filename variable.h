#ifndef VARIABLE_H
#define VARIABLE_H

#include <QList>
#include <QString>
#include "instrument.h"

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
  
private:
  int id;
  QList<double> values;
  QString name;
  int instrument_id;
};

#endif // VARIABLE_H