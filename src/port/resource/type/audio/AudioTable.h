#pragma once

#include <cstdint>
#include <Resource.h>

namespace SF64 {
struct AudioTableBase {
    /* 0x00 */ int16_t numEntries;
    /* 0x02 */ int16_t unkMediumParam;
    /* 0x04 */ uintptr_t romAddr;
    /* 0x08 */ char pad[8];
};

struct AudioTableEntry {
    /* 0x00 */ uintptr_t romAddr;
    /* 0x04 */ uint32_t size;
    /* 0x08 */ int8_t medium;
    /* 0x09 */ int8_t cachePolicy;
    /* 0x0A */ int16_t shortData1;
    /* 0x0C */ int16_t shortData2;
    /* 0x0E */ int16_t shortData3;
}; // size = 0x10

struct AudioTableData {
    /* 0x00 */ AudioTableBase base;
    /* 0x10 */ AudioTableEntry* entries;
};

class AudioTable : public Ship::Resource<AudioTableData> {
  public:
    using Resource::Resource;

    AudioTable() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    AudioTableData* GetPointer();
    size_t GetPointerSize();

    AudioTableData mTable;
    std::vector<AudioTableEntry> mEntries;
};
}