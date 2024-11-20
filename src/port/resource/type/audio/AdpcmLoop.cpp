#include "AdpcmLoop.h"

namespace SF64 {
AdpcmLoopData* AdpcmLoop::GetPointer() {
    return &mLoop;
}

size_t AdpcmLoop::GetPointerSize() {
    return sizeof(AdpcmLoopData);
}
}