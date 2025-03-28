#include "InstrumentFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Instrument.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryInstrumentV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                 std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto instrument = std::make_shared<Instrument>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    instrument->mInstrument.isRelocated = reader->ReadUByte();
    instrument->mInstrument.normalRangeLo = reader->ReadUByte();
    instrument->mInstrument.normalRangeHi = reader->ReadUByte();
    instrument->mInstrument.adsrDecayIndex = reader->ReadUByte();
    instrument->mInstrument.envelope = LoadChild<EnvelopePointData*>(reader->ReadUInt64());
    auto lowSample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.lowPitchTunedSample.sample = lowSample;
    instrument->mInstrument.lowPitchTunedSample.tuning =
        lowSample != nullptr && lowSample->tuning != 0.0f ? lowSample->tuning : reader->ReadFloat();

    auto normalSample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.normalPitchTunedSample.sample = normalSample;
    instrument->mInstrument.normalPitchTunedSample.tuning =
        normalSample != nullptr && normalSample->tuning != 0.0f ? normalSample->tuning : reader->ReadFloat();

    auto highSample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.highPitchTunedSample.sample = highSample;
    instrument->mInstrument.highPitchTunedSample.tuning =
        highSample != nullptr && highSample->tuning != 0.0f ? highSample->tuning : reader->ReadFloat();
    instrument->mInstrument.isRelocated = 1;

    return instrument;
}
} // namespace LUS
