#pragma once

#include "resource/Resource.h"
namespace SF64 {

class Text : public Ship::Resource<void> {
  public:
    using Resource::Resource;

    Text();

    void* GetPointer() override;
    size_t GetPointerSize() override;

    std::string Data;
};
}; // namespace SF64