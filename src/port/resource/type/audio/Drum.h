#pragma once

#include <cstdint>
#include <Resource.h>
#include "Envelope.h"
#include "AudioContext.h"

namespace SF64 {
struct DrumData {
    uint8_t adsrDecayIndex;
    uint8_t pan;
    uint8_t isRelocated;
    TunedSample tunedSample;
    EnvelopePointData* envelope;
};

class Drum : public Ship::Resource<DrumData> {
  public:
    using Resource::Resource;

    Drum() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    DrumData* GetPointer();
    size_t GetPointerSize();

    DrumData mDrum;
};
}