#include "experiment.h"

Experiment::Experiment(QList<Variable>& vars, 
  QList<class Constant>& cons, 
  QList<class Instrument>& ins)
: variables(vars), constants(cons), instruments(ins) {}

Experiment::Experiment() : variables(), constants(), instruments(){
}

Experiment* Experiment::getInstance() {
    if (instance == nullptr) {
        instance = new Experiment();
    }
    return instance;
}

Experiment* Experiment::instance = nullptr;
  
const QList<Variable>& Experiment::getVariables() const {
    return variables;
}

QList<Variable>& Experiment::getVariables() {
    return variables;
}

const QList<Constant>& Experiment::getConstants() const {
    return constants;
}

QList<Constant>& Experiment::getConstants() {
    return constants;
}

const QList<Instrument>& Experiment::getInstruments() const {
    return instruments;
}

QList<Instrument>& Experiment::getInstruments() {
    return instruments;
}

Instrument& Experiment::getInstrument(int i) {
    return instruments[i];
}

void Experiment::setVariables(const QList<Variable>& vars) {
    variables = vars;
}

void Experiment::setConstants(const QList<Constant>& cons) {
    constants = cons;
}

void Experiment::setInstruments(const QList<Instrument>& inst) {
    instruments = inst;
}