#include "SampleFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Sample.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinarySampleV1::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto sample = std::make_shared<Sample>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    sample->mSample.codec = reader->ReadUInt32();
    sample->mSample.medium = reader->ReadUInt32();
    sample->mSample.unk = reader->ReadUInt32();
    sample->mSample.size = reader->ReadUInt32();
    sample->mSample.loop = LoadChild<AdpcmLoopData*>(reader->ReadUInt64());
    sample->mSample.book = LoadChild<AdpcmBookData*>(reader->ReadUInt64());
    sample->mSample.sampleAddr = new uint8_t[sample->mSample.size];
    reader->Read((char*) sample->mSample.sampleAddr, sample->mSample.size);

    sample->mSample.medium = 0;
    sample->mSample.isRelocated = 1;

    return sample;
}
} // namespace LUS
