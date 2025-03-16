#pragma once

#include "Resource.h"
#include "ResourceFactoryXML.h"
#include "ResourceFactoryBinary.h"

namespace SF64 {
struct OggFileData {
    void* data;
    size_t pos;
    size_t size;
};

class ResourceFactoryBinarySampleV1 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};

class ResourceFactoryXMLSampleV0 : public Ship::ResourceFactoryXML {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
  private:
    static uint8_t CodecStrToInt(const char* str, const char* file);
    static uint32_t MediumStrToInt(const char* str);
};
}; // namespace LUS
