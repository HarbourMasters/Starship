#include "Sample.h"

namespace SF64 {
SampleData* Sample::GetPointer() {
    return &mSample;
}

size_t Sample::GetPointerSize() {
    return sizeof(mSample);
}
}