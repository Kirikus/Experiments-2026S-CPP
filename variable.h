#ifndef VARIABLE_H
#define VARIABLE_H

#include <QList>
#include <QString>
#include "instrument.h"

class Variable{
public:
  Variable(QList<double> values, QString name, const Instrument* inst);
  Variable();

  QList<double>& get_values();
  const QString& get_name();
  const Instrument* get_instrument() const;

  void set_values(QList<double>& new_values);
  void add_value(double new_value);
  void set_name(const QString& new_name);
  void set_instrument(const Instrument* instrument);
  int get_id() const;
  void set_id(int id);
  
private:
  int id;
  QList<double> values;
  QString name;
  const Instrument* instrument;
};

#endif // VARIABLE_H