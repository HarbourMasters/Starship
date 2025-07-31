#pragma once

#include "Limb.h"

#include <cstdint>
#include <Resource.h>

namespace SF64 {

struct ObjectInitData {
    /* 0x00 */ float zPos1;
    /* 0x04 */ int16_t zPos2;
    /* 0x06 */ int16_t xPos;
    /* 0x08 */ int16_t yPos;
    /* 0x0A */ Vec3s rot;
    /* 0x10 */ int16_t id;
}; // size = 0x14

// Renamed from ObjectInit to prevent clashing with Torch of same namespace
class ObjectInitResource : public Ship::Resource<ObjectInitData> {
  public:
    using Resource::Resource;

    ObjectInitResource() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {}

    ObjectInitData* GetPointer();
    size_t GetPointerSize();

    std::vector<ObjectInitData> mObjects;
};
}