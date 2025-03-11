#include "TextFactory.h"
#include "../type/Text.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryTextV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto text = std::make_shared<Text>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    text->Data = reader->ReadCString();
    return text;
}
} // namespace SF64