#pragma once

#include <cstdint>
#include <Resource.h>

namespace SF64 {
struct AdpcmBookData {
    /* 0x00 */ int32_t order;
    /* 0x04 */ int32_t numPredictors;
    /* 0x08 */ int16_t* book;
};

class AdpcmBook : public Ship::Resource<AdpcmBookData> {
  public:
    using Resource::Resource;

    AdpcmBook() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    AdpcmBookData* GetPointer();
    size_t GetPointerSize();

    AdpcmBookData mBook;
    std::vector<int16_t> mPages;
};
}