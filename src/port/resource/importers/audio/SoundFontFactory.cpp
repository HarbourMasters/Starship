#include "SoundFontFactory.h"
#include "../ResourceUtil.h"
#include "utils/StringHelper.h"
#include <sf64audio_provisional.h>
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

int8_t ResourceFactoryXMLSoundFontV0::MediumStrToInt(const char* str) {
    if (!strcmp("Ram", str)) {
        return MEDIUM_RAM;
    } else if (!strcmp("Unk", str)) {
        return MEDIUM_UNK;
    } else if (!strcmp("Cart", str)) {
        return MEDIUM_CART;
    } else if (!strcmp("Disk", str)) {
        return MEDIUM_DISK_DRIVE;
        // 4 is skipped
    } else {
        throw std::runtime_error(
            StringHelper::Sprintf("Bad medium value. Got %s, expected Ram, Unk, Cart, or Disk.", str));
    }
}

int8_t ResourceFactoryXMLSoundFontV0::CachePolicyToInt(const char* str) {
    if (!strcmp("Temporary", str)) {
        return CACHE_TEMPORARY;
    } else if (!strcmp("Persistent", str)) {
        return CACHE_PERSISTENT;
    } else if (!strcmp("Either", str)) {
        return CACHE_EITHER;
    } else if (!strcmp("Permanent", str)) {
        return CACHE_PERMANENT;
    } else {
        throw std::runtime_error(StringHelper::Sprintf(
            "Bad cache policy value. Got %s, expected Temporary, Persistent, Either, or Permanent.", str));
    }
}

void ResourceFactoryXMLSoundFontV0::ParseDrums(SoundFont* soundFont, tinyxml2::XMLElement* element) {
    element = (tinyxml2::XMLElement*)element->FirstChildElement();
    // No drums
    if (element == nullptr) {
        soundFont->mFont.drums = nullptr;
        soundFont->mFont.numDrums = 0;
        return;
    }

    do {
        auto drum = new DrumData;
        std::vector<EnvelopePointData> envelopes;
        drum->adsrDecayIndex = element->IntAttribute("ReleaseRate");
        drum->pan = element->IntAttribute("Pan");
        drum->isRelocated = element->IntAttribute("Loaded");
        drum->tunedSample.tuning = element->FloatAttribute("Tuning");
        const char* sampleStr = element->Attribute("SampleRef");

        if (sampleStr != nullptr && sampleStr[0] != 0) {
            auto res = Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(sampleStr);
            drum->tunedSample.sample = static_cast<SampleData*>(res ? res->GetRawPointer() : nullptr);
        } else {
            drum->tunedSample.sample = nullptr;
        }

        element = (tinyxml2::XMLElement*)element->FirstChildElement();
        if (!strcmp(element->Name(), "Envelopes")) {
            // element = (tinyxml2::XMLElement*)element->FirstChildElement();
            unsigned int envCount = 0;
            envelopes = ParseEnvelopes(soundFont, element, &envCount);
            element = (tinyxml2::XMLElement*)element->Parent();
            drum->envelope = new EnvelopePointData[envelopes.size()];
            memcpy(drum->envelope, envelopes.data(), envelopes.size() * sizeof(EnvelopePointData));
        } else {
            drum->envelope = nullptr;
        }

        if (drum->tunedSample.sample == nullptr) {
            soundFont->mDrums.push_back(nullptr);
        } else {
            soundFont->mDrums.push_back(drum);
        }

        element = element->NextSiblingElement();
    } while (element != nullptr);

    soundFont->mFont.numDrums = soundFont->mDrums.size();
    soundFont->mFont.drums = soundFont->mDrums.data();
}

void ResourceFactoryXMLSoundFontV0::ParseInstruments(SoundFont* soundFont, tinyxml2::XMLElement* element) {
    element = element->FirstChildElement();
    do {
        auto instrument = new InstrumentData;
        unsigned int envCount = 0;
        std::vector<EnvelopePointData> envelopes;

        int isValid = element->BoolAttribute("IsValid");
        instrument->isRelocated = element->IntAttribute("Loaded");
        instrument->normalRangeLo = element->IntAttribute("NormalRangeLo");
        instrument->normalRangeHi = element->IntAttribute("NormalRangeHi");
        instrument->adsrDecayIndex = element->IntAttribute("ReleaseRate");
        tinyxml2::XMLElement* instrumentElement = element->FirstChildElement();
        tinyxml2::XMLElement* instrumentElementCopy = instrumentElement;

        if (instrumentElement != nullptr && !strcmp(instrumentElement->Name(), "Envelopes")) {
            envelopes = ParseEnvelopes(soundFont, instrumentElement, &envCount);
            instrument->envelope = new EnvelopePointData[envelopes.size()];
            memcpy(instrument->envelope, envelopes.data(), envelopes.size() * sizeof(EnvelopePointData));
            instrumentElement = instrumentElement->NextSiblingElement();
        }

        if (instrumentElement != nullptr && !strcmp("LowNotesSound", instrumentElement->Name())) {
            instrument->lowPitchTunedSample.tuning = instrumentElement->FloatAttribute("Tuning");
            const char* sampleStr = instrumentElement->Attribute("SampleRef");
            if (sampleStr != nullptr && sampleStr[0] != 0) {
                auto res = static_pointer_cast<Sample>(
                    Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(sampleStr, true));
                auto sample = static_cast<SampleData*>(res ? res->GetRawPointer() : nullptr);
                instrument->lowPitchTunedSample.sample = sample;
                if (sample != nullptr && sample->tuning != 0.0f) {
                    instrument->lowPitchTunedSample.tuning = sample->tuning;
                }
            }
            instrumentElement = instrumentElement->NextSiblingElement();
        }

        if (instrumentElement != nullptr && !strcmp("NormalNotesSound", instrumentElement->Name())) {
            instrument->normalPitchTunedSample.tuning = instrumentElement->FloatAttribute("Tuning");
            const char* sampleStr = instrumentElement->Attribute("SampleRef");
            if (sampleStr != nullptr && sampleStr[0] != 0) {
                auto res = static_pointer_cast<Sample>(
                    Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(sampleStr, true));
                auto sample = static_cast<SampleData*>(res ? res->GetRawPointer() : nullptr);
                instrument->normalPitchTunedSample.sample = sample;
                if (sample != nullptr && sample->tuning != 0.0f) {
                    instrument->normalPitchTunedSample.tuning = sample->tuning;
                }
            }
            instrumentElement = instrumentElement->NextSiblingElement();
        }

        if (instrumentElement != nullptr && !strcmp("HighNotesSound", instrumentElement->Name())) {
            instrument->highPitchTunedSample.tuning = instrumentElement->FloatAttribute("Tuning");
            const char* sampleStr = instrumentElement->Attribute("SampleRef");
            if (sampleStr != nullptr && sampleStr[0] != 0) {
                auto res = static_pointer_cast<Sample>(
                    Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(sampleStr, true));
                auto sample = static_cast<SampleData*>(res ? res->GetRawPointer() : nullptr);
                instrument->highPitchTunedSample.sample = sample;
                if (sample != nullptr && sample->tuning != 0.0f) {
                    instrument->highPitchTunedSample.tuning = sample->tuning;
                }
            }
            instrumentElement = instrumentElement->NextSiblingElement();
        }

        soundFont->mInstruments.push_back(instrument);

        element = instrumentElementCopy;
        element = (tinyxml2::XMLElement*)element->Parent();
        element = element->NextSiblingElement();
    } while (element != nullptr);

    soundFont->mFont.instruments = soundFont->mInstruments.data();
    soundFont->mFont.numInstruments = soundFont->mInstruments.size();
}

std::vector<EnvelopePointData> ResourceFactoryXMLSoundFontV0::ParseEnvelopes(SoundFont* soundFont,
                                                                             tinyxml2::XMLElement* element,
                                                                             unsigned int* count) {
    std::vector<EnvelopePointData> envelopes;
    unsigned int total = 0;
    element = element->FirstChildElement("Envelope");
    while (element != nullptr) {
        EnvelopePointData env = {
            .delay = (s16)element->IntAttribute("Delay"),
            .arg = (s16)element->IntAttribute("Arg"),
        };
        envelopes.emplace_back(env);
        element = element->NextSiblingElement("Envelope");
        total++;
    }
    *count = total;
    return envelopes;
}

std::shared_ptr<Ship::IResource> ResourceFactoryXMLSoundFontV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }
    auto audioSoundFont = std::make_shared<SoundFont>(file->InitData);
    auto child = std::get<std::shared_ptr<tinyxml2::XMLDocument>>(file->Reader)->FirstChildElement();
    // Header data
    memset(&audioSoundFont->mFont, 0, sizeof(audioSoundFont->mFont));

    auto shortData1 = child->IntAttribute("Data1");
    auto shortData2 = child->IntAttribute("Data2");

    audioSoundFont->mFont.numInstruments = (shortData2 >> 8) & 0xFFu;
    audioSoundFont->mFont.numDrums = shortData2 & 0xFFu;
    audioSoundFont->mFont.sampleBankId1 = (shortData1 >> 8) & 0xFFu;
    audioSoundFont->mFont.sampleBankId2 = shortData1 & 0xFFu;

    child = (tinyxml2::XMLElement*)child->FirstChildElement();

    while (child != nullptr) {
        const char* name = child->Name();

        if (!strcmp(name, "Drums")) {
            ParseDrums(audioSoundFont.get(), child);
        } else if (!strcmp(name, "Instruments")) {
            ParseInstruments(audioSoundFont.get(), child);
        }
        child = child->NextSiblingElement();
    }
    return audioSoundFont;
}
} // namespace LUS
