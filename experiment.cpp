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

QJsonObject Experiment::to_json() const {

    QJsonObject experiment_json;
    QJsonArray variables_json;
    QJsonArray constants_json;
    QJsonArray instruments_json;
    QList<int> inst_keys = instruments.keys();
    std::sort(inst_keys.begin(), inst_keys.end());

    for (int i = 0; i < variables.size(); i++) {
        variables_json.append(variables[i].to_json());
    }

    for (int i = 0; i < constants.size(); i++) {
        constants_json.append(constants[i].to_json());
    }

    for (int key : inst_keys) {
        instruments_json.append(instruments[key].to_json());
    }

    experiment_json["Constants"] = constants_json;
    experiment_json["Variables"] = variables_json;
    experiment_json["Instruments"] = instruments_json;

    return experiment_json;
    
}


bool Experiment::from_json(const QJsonObject& root, QString& error) {
    // Очистка текущих данных
    variables.clear();
    constants.clear();
    instruments.clear();

    // --- Загрузка инструментов ---
    if (!root.contains("Instruments") || !root["Instruments"].isArray()) {
        error = "Отсутствует или неверный формат секции 'Instruments'";
        return false;
    }
    QHash<int, Instrument> newInstruments;
    for (const auto& val : root["Instruments"].toArray()) {
        if (!val.isObject()) {
            error = "Элемент массива Instruments не является объектом";
            return false;
        }
        Instrument inst;
        if (!Instrument::from_json(val.toObject(), inst, error))
            return false;
        if (newInstruments.contains(inst.get_id())) {
            error = QString("Дубликат id инструмента: %1").arg(inst.get_id());
            return false;
        }
        newInstruments.insert(inst.get_id(), inst);
    }
    instruments = newInstruments;

    // --- Загрузка констант ---
    if (!root.contains("Constants") || !root["Constants"].isArray()) {
        error = "Отсутствует или неверный формат секции 'Constants'";
        return false;
    }
    QList<Constant> newConstants;
    for (const auto& val : root["Constants"].toArray()) {
        if (!val.isObject()) {
            error = "Элемент массива Constants не является объектом";
            return false;
        }
        Constant cons;
        if (!Constant::fromJson(val.toObject(), cons, error))
            return false;
        if (std::find_if(newConstants.begin(), newConstants.end(),
                         [&](const Constant& c) { return c.get_id() == cons.get_id(); }) != newConstants.end()) {
            error = QString("Дубликат id константы: %1").arg(cons.get_id());
            return false;
        }
        newConstants.append(cons);
    }
    constants = newConstants;

    // --- Загрузка переменных ---
    if (!root.contains("Variables") || !root["Variables"].isArray()) {
        error = "Отсутствует или неверный формат секции 'Variables'";
        return false;
    }
    QList<Variable> newVariables;
    for (const auto& val : root["Variables"].toArray()) {
        if (!val.isObject()) {
            error = "Элемент массива Variables не является объектом";
            return false;
        }
        Variable var;
        if (!Variable::fromJson(val.toObject(), instruments, var, error))
            return false;
        if (std::find_if(newVariables.begin(), newVariables.end(),
                         [&](const Variable& v) { return v.get_id() == var.get_id(); }) != newVariables.end()) {
            error = QString("Дубликат id переменной: %1").arg(var.get_id());
            return false;
        }
        newVariables.append(var);
    }
    variables = newVariables;

    // Обновление счётчиков ID (максимальный ID + 1)
    int maxVarId = 0, maxInstId = 0, maxConstId = 0;
    for (const auto& v : variables) if (v.get_id() > maxVarId) maxVarId = v.get_id();
    for (const auto& i : instruments) if (i.get_id() > maxInstId) maxInstId = i.get_id();
    for (const auto& c : constants) if (c.get_id() > maxConstId) maxConstId = c.get_id();

    set_variable_id(maxVarId);
    set_instrument_id(maxInstId);
    set_constant_id(maxConstId);

    return true;
}