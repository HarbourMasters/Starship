#include "MessageLookupFactory.h"
#include "../type/Message.h"
#include "spdlog/spdlog.h"
#include "resourcebridge.h"
#include "ResourceUtil.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryMessageLookupV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                    std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto table = std::make_shared<MessageLookup>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);
    auto count = reader->ReadUInt32();

    for (uint32_t i = 0; i < count - 1; i++) {
        auto id = reader->ReadInt32();
        auto crc = reader->ReadUInt64();

        uint16_t* ptr = LoadChild<uint16_t*>(crc);
        const char* name = ResourceGetNameByCrc(crc);
        table->mLookupTable.push_back({ id, ptr, strdup(name) });
    }

    return table;
}
} // namespace LUS
