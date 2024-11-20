#pragma once

#include <cstdint>
#include <Resource.h>
#include "Envelope.h"
#include "AudioContext.h"

namespace SF64 {
struct InstrumentData {
    uint8_t isRelocated;
    uint8_t normalRangeLo;
    uint8_t normalRangeHi;
    uint8_t adsrDecayIndex;
    EnvelopePointData* envelope;
    TunedSample lowPitchTunedSample;
    TunedSample normalPitchTunedSample;
    TunedSample highPitchTunedSample;
};

class Instrument : public Ship::Resource<InstrumentData> {
  public:
    using Resource::Resource;

    Instrument() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    InstrumentData* GetPointer();
    size_t GetPointerSize();

    InstrumentData mInstrument;
};
}