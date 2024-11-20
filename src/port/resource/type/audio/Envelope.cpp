#include "Envelope.h"

namespace SF64 {
EnvelopePointData* Envelope::GetPointer() {
    return mPoints.data();
}

size_t Envelope::GetPointerSize() {
    return sizeof(EnvelopePointData) * mPoints.size();
}
}