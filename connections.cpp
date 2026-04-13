#include "connections.h"

Connections::Connections() {}

void Connections::add_connection(Instrument* inst, Variable* var) {
    if (inst && var) {
        data.append(qMakePair(inst, var));
    }
}