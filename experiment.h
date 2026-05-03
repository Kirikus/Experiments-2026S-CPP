#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QList>
#include <QHash>
#include "instrument.h"
#include "variable.h"
#include "constant.h"

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


