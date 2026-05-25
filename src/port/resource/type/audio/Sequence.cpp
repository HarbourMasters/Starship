#include "Sequence.h"

namespace SF64 {
SequenceData* Sequence::GetPointer() {
    return reinterpret_cast<SequenceData*>(mBuffer.data());
}

size_t Sequence::GetPointerSize() {
    return mBuffer.size();
}
} // namespace SF64
