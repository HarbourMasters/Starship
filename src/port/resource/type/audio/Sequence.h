#pragma once

#include <cstdint>
#include <vector>
#include <Resource.h>

namespace SF64 {
struct SequenceData {
    uint32_t seqDataSize;
    char*    seqData;
    uint8_t  seqNumber;
    uint8_t  medium;
    uint8_t  cachePolicy;
    uint32_t numFonts;
    uint8_t  fonts[16];
};

class Sequence : public Ship::Resource<SequenceData> {
  public:
    using Resource::Resource;

    Sequence() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    SequenceData* GetPointer();
    size_t GetPointerSize();

    SequenceData mSequence;
    std::vector<char> mBuffer;
};
} // namespace SF64
