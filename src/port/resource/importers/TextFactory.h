#pragma once

#include "resource/Resource.h"
#include "resource/ResourceFactoryBinary.h"

namespace SF64 {
class ResourceFactoryBinaryTextV0 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file) override;
};
}; // namespace SF64
