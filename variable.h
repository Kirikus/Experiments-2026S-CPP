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
private:
  QList<double> values;
  QString name;
};

#endif // VARIABLE_H