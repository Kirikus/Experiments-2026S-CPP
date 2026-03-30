#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>

class Constant
{
public:
  Constant(QString &name, double &value, QString &meaning, bool readonly);

  QString get_name();
  double get_value();
  QString get_meaning();

  void set_name(QString &name);
  void set_value(double &value);
  void set_meaning(QString &meaning);

private:
  QString name;
  double value;
  QString meaning;
  bool readonly; // false для ввода
};

#endif // CONSTANT_H