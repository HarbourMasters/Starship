#include "EnvelopeFactory.h"
#include "port/resource/type/audio/Envelope.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryEnvelopeV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                               std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto envelope = std::make_shared<Envelope>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    uint32_t count = reader->ReadUInt32();
    for(size_t i = 0; i < count; i++){
        envelope->mPoints.push_back({ reader->ReadInt16(), reader->ReadInt16() });
    }

    return envelope;
}
} // namespace LUS
