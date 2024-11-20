#include "AudioTable.h"

namespace SF64 {
AudioTableData* AudioTable::GetPointer() {
    return &mTable;
}

size_t AudioTable::GetPointerSize() {
    return sizeof(AudioTableData);
}
}