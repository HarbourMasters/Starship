#include "DrumFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Drum.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryDrumV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto drum = std::make_shared<Drum>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    drum->mDrum.adsrDecayIndex = reader->ReadUByte();
    drum->mDrum.pan = reader->ReadUByte();
    drum->mDrum.isRelocated = reader->ReadUByte();
    drum->mDrum.tunedSample.sample = LoadChild<SampleData*>(reader->ReadUInt64());
    drum->mDrum.tunedSample.tuning = reader->ReadFloat();
    drum->mDrum.envelope = LoadChild<EnvelopePointData*>(reader->ReadUInt64());
    drum->mDrum.isRelocated = 1;

    return drum;
}
} // namespace LUS
