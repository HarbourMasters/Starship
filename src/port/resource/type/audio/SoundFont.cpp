#include "SoundFont.h"

namespace SF64 {
SoundFontData* SoundFont::GetPointer() {
    return &mFont;
}

size_t SoundFont::GetPointerSize() {
    return sizeof(SoundFontData);
}
}