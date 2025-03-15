#pragma once
#ifdef __cplusplus

#include "Resource.h"
#include "ResourceFactoryXML.h"
#include "ResourceFactoryBinary.h"

namespace SF64 {
class ResourceFactoryBinaryMessageV0 : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file) override;
};

class ResourceFactoryXMLMessageV0 : public Ship::ResourceFactoryXML {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file) override;
};
}; // namespace LUS
#else
extern int16_t Message_SearchCustomID(uint16_t* msg);
#endif