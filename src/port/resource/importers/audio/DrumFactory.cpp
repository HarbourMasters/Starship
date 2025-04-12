#include "DrumFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Drum.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryDrumV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                           std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto drum = std::make_shared<Drum>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    drum->mDrum.adsrDecayIndex = reader->ReadUByte();
    drum->mDrum.pan = reader->ReadUByte();
    drum->mDrum.isRelocated = reader->ReadUByte();
    auto sample = LoadChild<SampleData*>(reader->ReadUInt64());
    drum->mDrum.tunedSample.sample = sample;
    drum->mDrum.tunedSample.tuning = sample->tuning != 0.0f ? sample->tuning : reader->ReadFloat();
    drum->mDrum.envelope = LoadChild<EnvelopePointData*>(reader->ReadUInt64());
    drum->mDrum.isRelocated = 1;

    return drum;
}
} // namespace LUS
