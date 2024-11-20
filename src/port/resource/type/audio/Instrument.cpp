#include "Instrument.h"

namespace SF64 {
InstrumentData* Instrument::GetPointer() {
    return &mInstrument;
}

size_t Instrument::GetPointerSize() {
    return sizeof(InstrumentData);
}
}