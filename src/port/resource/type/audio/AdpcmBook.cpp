#include "AdpcmBook.h"

namespace SF64 {
AdpcmBookData* AdpcmBook::GetPointer() {
    return &mBook;
}

size_t AdpcmBook::GetPointerSize() {
    return sizeof(AdpcmBookData) + sizeof(int16_t) * mPages.size();
}
}