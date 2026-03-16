#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QString>

class Instrument {
public:
  Instrument(const QString& name, double error_value);
  double get_error_value() const;
  const QString& get_name() const;
  const QString& get_error_type() const;

protected:
  QString name;        //   название инструмента
  double error_value;  
  QString error_type; // тип ошибки (абсолютная, относительная)

};

#endif // INSTRUMENT_H