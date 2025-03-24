#include "ColPolyFactory.h"
#include "../type/ColPoly.h"
#include "spdlog/spdlog.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryColPolyV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                              std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto colPoly = std::make_shared<ColPoly>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    auto colPolysCount = reader->ReadUInt32();

    SPDLOG_INFO("ColPolyCount: {}", colPolysCount);

    for (uint32_t i = 0; i < colPolysCount; i++) {
        uint16_t triX  = reader->ReadUInt16();
        uint16_t triY  = reader->ReadUInt16();
        uint16_t triZ  = reader->ReadUInt16();
        Vec3s tri = {triX, triY, triZ};
        uint16_t normX = reader->ReadUInt16();
        uint16_t normY = reader->ReadUInt16();
        uint16_t normZ = reader->ReadUInt16();
        Vec3s norm = {normX, normY, normZ};
        uint32_t dist  = reader->ReadInt32();
        colPoly->mColPolys.emplace_back(tri, 0, norm, 0, dist);
    }

    return colPoly;
}
} // namespace LUS
