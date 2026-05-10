#ifndef CONSTANT_H
#define CONSTANT_H

#include <QString>
#include <QJsonObject>

class Constant
{
public:
  Constant(const QString &name, double value, double error, const QString &meaning, bool readonly);

  QString get_name() const;
  double get_value() const;
  double get_error() const;
  QString get_meaning() const;

  void set_name(const QString &name);
  void set_value(double value);
  void set_error(double value);
  void set_meaning(const QString &meaning);
  bool get_readonly() const;
  int get_id() const;
  void set_id(int new_id);
  QJsonObject to_json() const;
  static bool fromJson(const QJsonObject& obj, Constant& out, QString& error);

private:
  int id;
  QString name;
  double value;
  double error;
  QString meaning;
  bool readonly; // false для ввода
};

#endif // CONSTANT_H