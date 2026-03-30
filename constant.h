#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>

class Constant
{
public:
  Constant(const QString &name, double value, const QString &meaning, bool readonly);

  QString get_name() const;
  double get_value() const;
  QString get_meaning() const;

  void set_name(const QString &name);
  void set_value(double value);
  void set_meaning(const QString &meaning);

private:
  QString name;
  double value;
  QString meaning;
  bool readonly; // false для ввода
};

#endif // CONSTANT_H