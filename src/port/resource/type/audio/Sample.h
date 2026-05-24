#pragma once

#include <cstdint>
#include <ship/resource/Resource.h>
#include "Envelope.h"
#include "AdpcmLoop.h"
#include "AdpcmBook.h"

namespace SF64 {
struct SampleData {
    uint32_t codec : 4;
    uint32_t medium : 2;
    uint32_t unk : 1;
    uint32_t isRelocated : 1;
    uint32_t size;
    uint8_t* sampleAddr;
    AdpcmLoopData* loop;
    AdpcmBookData* book;
    float tuning = 0.0f;
    uint32_t channels = 1;
    uint32_t sampleRate = 32000;
    uint32_t numFrames = 0;
};

class Sample : public Ship::Resource<SampleData> {
  public:
    using Resource::Resource;

    Sample() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    SampleData* GetPointer();
    size_t GetPointerSize();

    SampleData mSample;
};
}