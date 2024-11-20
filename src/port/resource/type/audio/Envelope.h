#pragma once

#include <cstdint>
#include <Resource.h>

namespace SF64 {

struct EnvelopePointData {
    int16_t delay;
    int16_t arg;
};

class Envelope : public Ship::Resource<EnvelopePointData> {
  public:
    using Resource::Resource;

    Envelope() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    EnvelopePointData* GetPointer();
    size_t GetPointerSize();

    std::vector<EnvelopePointData> mPoints;
};
}