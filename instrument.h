#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QString>

class Instrument {
public:
  Instrument(const QString& name, double error_value);
  double get_error_value() const;
  const QString& get_name() const;
  const QString& get_error_type() const;
  void set_error_value(double new_error_value);
  void set_name(QString& new_name);
  void get_error_type(QString& new_error_type);

protected:
  QString name;        //   название инструмента
  double error_value;  
  QString error_type; // тип ошибки (абсолютная, относительная)

};

#endif // INSTRUMENT_H