#pragma once

#include "Resource.h"
#include "ResourceFactoryXML.h"
#include "ResourceFactoryBinary.h"
#include "port/resource/type/audio/Sequence.h"
#include "SoundFontFactory.h"

namespace SF64 {

class ResourceFactoryBinarySequenceV2 : public Ship::ResourceFactoryBinary {
  public:
    virtual ~ResourceFactoryBinarySequenceV2() = default;
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};

class ResourceFactoryXMLSequenceV0 : public Ship::ResourceFactoryXML {
  public:
    virtual ~ResourceFactoryXMLSequenceV0() = default;
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};

} // namespace SF64
