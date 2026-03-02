#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>

class Constant {
public:
  Constant(double& value, double& error, QString& name, bool readonly);
  double get_value() const;
  double get_error() const;
  QString get_name() const;


private:

  double value;
  double error;
  QString name;
  bool readonly;      // True для подсчитанный (пр. mean(X)), False для введенных (g)
};

#endif // CONSTANT_H