#pragma once

#include <cstdint>
#include <Resource.h>

namespace SF64 {
struct AdpcmLoopData {
    /* 0x00 */ uint32_t start;
    /* 0x04 */ uint32_t end;
    /* 0x08 */ uint32_t count;
    /* 0x10 */ int16_t predictorState[16]; // only exists if count != 0. 8-byte aligned
};

class AdpcmLoop : public Ship::Resource<AdpcmLoopData> {
  public:
    using Resource::Resource;

    AdpcmLoop() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    AdpcmLoopData* GetPointer();
    size_t GetPointerSize();

    AdpcmLoopData mLoop;
};
}