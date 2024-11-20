#include "SoundFontFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/SoundFont.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinarySoundFontV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto font = std::make_shared<SoundFont>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    font->mFont.numInstruments = reader->ReadUByte();
    font->mFont.numDrums = reader->ReadUByte();
    font->mFont.sampleBankId1 = reader->ReadUByte();
    font->mFont.sampleBankId2 = reader->ReadUByte();

    for(size_t i = 0; i < font->mFont.numInstruments; i++){
        font->mInstruments.push_back(LoadChild<InstrumentData*>(reader->ReadUInt64()));
    }

    for(size_t i = 0; i < font->mFont.numDrums; i++){
        font->mDrums.push_back(LoadChild<DrumData*>(reader->ReadUInt64()));
    }

    font->mFont.instruments = font->mInstruments.data();
    font->mFont.drums = font->mDrums.data();

    return font;
}
} // namespace LUS
