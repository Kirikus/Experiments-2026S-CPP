#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QList>
#include "instrument.h"
#include "variable.h"
#include "constant.h"

class Experiment {   // Основной класс для хранения всех данных
public:          

  static Experiment* getInstance();

  Experiment(QList<class Variable>& variables, 
             QList<class Constant>& constants,
             QList<class Instrument>& instruments);
  Experiment();

  const QList<class Variable>& getVariables() const;

  const QList<class Constant>& getConstants() const;

  const QList<class Instrument>& getInstruments() const;

  void setVariables(const QList<class Variable>& vars);
  void setConstants(const QList<class Constant>& cons);
  void setInstruments(const QList<class Instrument>& inst);


private:

  static Experiment* instance;   // the one and only instance

  QList<class Variable> variables;
  QList<class Constant> constants;
  QList<class Instrument> instruments;
};

#endif // EXPERIMENT_H


