#pragma once

#include "Resource.h"
#include "ResourceFactoryXML.h"
#include "ResourceFactoryBinary.h"
#include "port/resource/type/audio/SoundFont.h"

namespace SF64 {
class ResourceFactoryBinarySoundFontV0 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
};

class ResourceFactoryXMLSoundFontV0 : public Ship::ResourceFactoryXML {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file,
                                                  std::shared_ptr<Ship::ResourceInitData> initData) override;
    static int8_t MediumStrToInt(const char* str);
    static int8_t CachePolicyToInt(const char* str);

  private:
    void ParseDrums(SoundFont* soundFont, tinyxml2::XMLElement* element);
    void ParseInstruments(SoundFont* soundFont, tinyxml2::XMLElement* element);
    std::vector<EnvelopePointData> ParseEnvelopes(SoundFont* soundFont, tinyxml2::XMLElement* element,
                                              unsigned int* count);
};
}; // namespace LUS
