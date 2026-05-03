#include "experiment.h"

Experiment::Experiment(QList<Variable>& vars, 
  QList<class Constant>& cons, 
  QHash<int, Instrument>& ins)
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

const QHash<int, Instrument>& Experiment::getInstruments() const {
    return instruments;
}

QHash<int, Instrument>& Experiment::getInstruments() {
    return instruments;
}

Instrument* Experiment::getInstrument(int id) {
    auto it = instruments.find(id);
    return it != instruments.end() ? &it.value() : nullptr;
}
const Instrument* Experiment::getInstrument(int id) const {
    auto it = instruments.find(id);
    return it != instruments.end() ? &it.value() : nullptr;
}

void Experiment::setVariables(const QList<Variable>& vars) {
    variables = vars;
}

void Experiment::setConstants(const QList<Constant>& cons) {
    constants = cons;
}

void Experiment::setInstruments(const QHash<int, Instrument>& inst) {
    instruments = inst;
}

void Experiment::addVariable(Variable& var) {
    var.set_id(variable_id++);
    variables.append(var);
}

void Experiment::addInstrument(Instrument& inst) {
    inst.set_id(instrument_id);
    instruments[instrument_id++] = inst;
}

void Experiment::addConstant(Constant& cons) {
    cons.set_id(constant_id++);
    constants.append(cons);
}

QString& Experiment::get_file_name() {
    return fileName;
}

void Experiment::set_file_name(QString& name) {
    fileName = name;
}