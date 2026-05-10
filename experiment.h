#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QList>
#include <QHash>
#include "instrument.h"
#include "variable.h"
#include "constant.h"
#include <QJsonObject>

class Experiment {   // Основной класс для хранения всех данных
public:          

  Experiment(const Experiment& obj) = delete;

  void operator=(const Experiment&) = delete;

  static Experiment* getInstance();

  const QList<class Variable>& getVariables() const;
  QList<class Variable>& getVariables();

  const QList<class Constant>& getConstants() const;
  QList<class Constant>& getConstants();

  const QHash<int, Instrument>& getInstruments() const;
  QHash<int, class Instrument>& getInstruments();

  Instrument* getInstrument(int id);
  const Instrument* getInstrument(int id) const;

  void setVariables(const QList<class Variable>& vars);
  void setConstants(const QList<class Constant>& cons);
  void setInstruments(const QHash<int, Instrument>& inst);

  void addVariable(Variable& var);
  void addInstrument(Instrument& inst);
  void addConstant(Constant& cons);

  QString& get_file_name();
  void set_file_name(QString& name);

  void set_variable_id(int new_id) { variable_id = new_id + 1; }
  void set_instrument_id(int new_id) { instrument_id = new_id + 1; }
  void set_constant_id(int new_id) { constant_id = new_id + 1; }
  
  QJsonObject to_json() const;

private:

  Experiment(QList<class Variable>& variables, 
             QList<class Constant>& constants,
             QHash<int, Instrument>& instruments);

  Experiment();

  static Experiment* instance;

  QList<class Variable> variables;
  QList<class Constant> constants;
  QHash<int, Instrument> instruments;

  unsigned long long variable_id = 1;
  unsigned long long instrument_id = 1;
  unsigned long long constant_id = 1;

  QString fileName;
};

#endif // EXPERIMENT_H


