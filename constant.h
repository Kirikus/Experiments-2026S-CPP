#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>

class Constant {
public:
  Constant(double& value, double& error, QString& name, bool readonly);
  double get_value();
  double get_error();
  QString get_name();

  void set_value(double& value);
  void set_error(double& error);
  void set_name(QString& name);


private:

  double value;
  double error;
  QString name;
  bool readonly;      // True для подсчитанных (пр. mean(X)), False для введенных (g)
};

#endif // CONSTANT_H