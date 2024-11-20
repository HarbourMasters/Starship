#include "AudioTableFactory.h"
#include "port/resource/type/audio/AudioTable.h"
#include "../ResourceUtil.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAudioTableV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto table = std::make_shared<AudioTable>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    int16_t med = reader->ReadInt16();
    uint32_t addr = reader->ReadUInt32();
    uint32_t count = reader->ReadUInt32();

    for(size_t i = 0; i < count; i++){
        uint64_t crc = reader->ReadUInt64();
        uint32_t size = reader->ReadUInt32();
        int8_t medium = reader->ReadInt8();
        int8_t policy = reader->ReadInt8();
        int16_t sd1 = reader->ReadInt16();
        int16_t sd2 = reader->ReadInt16();
        int16_t sd3 = reader->ReadInt16();

        table->mEntries.push_back({
            (uintptr_t) crc,
            size, medium, policy, sd1, sd2, sd3
        });
    }

    table->mTable.base = { (int16_t)count, med, addr };
    table->mTable.entries = table->mEntries.data();

    return table;
}
} // namespace LUS
