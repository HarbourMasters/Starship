#pragma once

#include <cstdint>
#include <Resource.h>
#include "Instrument.h"
#include "Drum.h"

namespace SF64 {
struct SoundFontData {
    /* 0x00 */ uint8_t numInstruments;
    /* 0x01 */ uint8_t numDrums;
    /* 0x02 */ uint8_t sampleBankId1;
    /* 0x03 */ uint8_t sampleBankId2;
    /* 0x04 */ InstrumentData** instruments;
    /* 0x08 */ DrumData** drums;
};

class SoundFont : public Ship::Resource<SoundFontData> {
  public:
    using Resource::Resource;

    SoundFont() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    SoundFontData* GetPointer();
    size_t GetPointerSize();

    SoundFontData mFont;
    std::vector<InstrumentData*> mInstruments;
    std::vector<DrumData*> mDrums;
};
}