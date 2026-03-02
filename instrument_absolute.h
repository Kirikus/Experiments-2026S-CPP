#ifndef INSTRUMENT_ABSOLUTE_H
#define INSTRUMENT_ABSOLUTE_H

#include "instrument.h"

class InstrumentAbsolute : public Instrument {
    InstrumentAbsolute(const QString& name, double error_value);
};

#endif // INSTRUMENT_ABSOLUTE_H