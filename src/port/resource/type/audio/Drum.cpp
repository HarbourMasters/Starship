#include "Drum.h"

namespace SF64 {
DrumData* Drum::GetPointer() {
    return &mDrum;
}

size_t Drum::GetPointerSize() {
    return sizeof(DrumData);
}
}