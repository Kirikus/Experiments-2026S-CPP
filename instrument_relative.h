#ifndef INSTRUMENT_RELATIVE_H
#define INSTRUMENT_RELATIVE_H

#include "instrument.h"

class InstrumentRelative : public Instrument {
public:    
  InstrumentRelative(const QString& name, double error_value);
private:
  
};

#endif // INSTRUMENT_RELATIVE_H