#ifndef VARIABLE_H
#define VARIABLE_H

#include <QList>
#include <QString>

class Variable{
public:
  Variable(QList<double> values, QString name);
  Variable();

  const QList<double>& get_values();
  const QString& get_name();

  void set_values(QList<double>& new_values);
  void add_value(double new_value);
  void set_name(const QString& new_name);
  
private:
  QList<double> values;
  QString name;
};

#endif // VARIABLE_H