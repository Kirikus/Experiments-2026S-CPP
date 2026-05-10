#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QString>
#include <QJsonObject>

class Instrument {
public:
  Instrument(const QString& name, double error_value);
  Instrument() = default;
  double get_error_value() const;
  const QString& get_name() const;
  const QString& get_error_type() const;
  void set_error_value(double new_error_value);
  void set_name(QString& new_name);
  void set_error_type(QString& new_error_type);
  int get_id() const;
  void set_id(int new_id);
  QJsonObject to_json() const;

protected:
  QString name;        //   название инструмента
  double error_value;  
  QString error_type; // тип ошибки (абсолютная, относительная)
  int id;

};

#endif // INSTRUMENT_H