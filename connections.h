#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "experiment.h"

class Connections {
public:
  Connections();
  void add_connection(Instrument* inst, Variable* var);

private:
    QList<QPair<Instrument*, Variable*>> data;
};

#endif // CONNECTIONS_H