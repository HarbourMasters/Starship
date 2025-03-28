#include "AnimFactory.h"
#include "../type/Animation.h"
#include "spdlog/spdlog.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAnimV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                           std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto anim = std::make_shared<Animation>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    int16_t frameCount = reader->ReadInt16();
    int16_t limbCount  = reader->ReadInt16();

    auto jointSize = reader->ReadUInt32();

    SPDLOG_INFO("JointSize: {}", jointSize);

    for (uint32_t i = 0; i < jointSize; i++) {
        uint16_t xLen = reader->ReadUInt16();
        uint16_t x    = reader->ReadUInt16();
        uint16_t yLen = reader->ReadUInt16();
        uint16_t y    = reader->ReadUInt16();
        uint16_t zLen = reader->ReadUInt16();
        uint16_t z    = reader->ReadUInt16();
        anim->jointKey.push_back({xLen, x, yLen, y, zLen, z});
    }

    auto frameSize = reader->ReadUInt32();

    for (uint32_t i = 0; i < frameSize; i++) {
        anim->frameData.push_back(reader->ReadInt16());
    }

    anim->mData.frameCount = frameCount;
    anim->mData.limbCount  = limbCount;
    anim->mData.jointKey   = anim->jointKey.data();
    anim->mData.frameData  = anim->frameData.data();

    return anim;
}
} // namespace LUS
