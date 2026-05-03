#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QList>
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

  const QList<class Instrument>& getInstruments() const;
  QList<class Instrument>& getInstruments();

  Instrument& getInstrument(int i);

  void setVariables(const QList<class Variable>& vars);
  void setConstants(const QList<class Constant>& cons);
  void setInstruments(const QList<class Instrument>& inst);

  void addVariable(Variable& var);
  void addInstrument(Instrument& inst);
  void addConstant(Constant& cons);

private:

  Experiment(QList<class Variable>& variables, 
             QList<class Constant>& constants,
             QList<class Instrument>& instruments);

  Experiment();

  static Experiment* instance;

  QList<class Variable> variables;
  QList<class Constant> constants;
  QList<class Instrument> instruments;

  unsigned long long variable_id = 1;
  unsigned long long instrument_id = 1;
  unsigned long long constant_id = 1;
};

#endif // EXPERIMENT_H


